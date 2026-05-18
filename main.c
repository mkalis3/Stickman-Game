#include <xc.h>
#include <stdint.h>
#include <sys/attribs.h>
#include <math.h>
#include <stdio.h> // For sprintf
//------------------------------------------------------------------------------
// Configuration Bits
//------------------------------------------------------------------------------
#pragma config JTAGEN   = OFF
#pragma config FWDTEN   = OFF
#pragma config FNOSC    = FRCPLL
#pragma config FSOSCEN  = OFF
#pragma config POSCMOD  = EC
#pragma config OSCIOFNC = ON
#pragma config FPBDIV   = DIV_1
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL  = MUL_20
#pragma config FPLLODIV = DIV_1

//------------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------------
#define SYS_FREQ  40000000UL
#define LCD_ROWS  2
#define LCD_COLS  16

// Board switches used for menu, difficulty, and restart controls.
#define SW0       PORTFbits.RF3  // Return to main menu
#define SW1       PORTFbits.RF5  // Difficulty: 0=normal, 1=hard
#define SW2       PORTFbits.RF4  // Restart
#define SW3       PORTDbits.RD15  // Restart

// Timer3 and OC1 drive square-wave sound output.
volatile int soundEnabled = 0;  // 1 => generate tone, 0 => silence

//------------------------------------------------------------------------------
// LCD Pins
//------------------------------------------------------------------------------
#define LCD_RS      LATBbits.LATB15
#define LCD_RW      LATDbits.LATD5
#define LCD_EN      LATDbits.LATD4
#define LCD_RS_TRIS TRISBbits.TRISB15
#define LCD_RW_TRIS TRISDbits.TRISD5
#define LCD_EN_TRIS TRISDbits.TRISD4
#define LCD_DATA    LATE
#define LCD_DATA_TRIS TRISE

//------------------------------------------------------------------------------
// Keypad Pins
// Rows = RC2, RC1, RC4, RG6 (outputs); Cols = RC3, RG7, RG8, RG9 (inputs).
//------------------------------------------------------------------------------
#define ROW1    LATCbits.LATC2
#define ROW2    LATCbits.LATC1
#define ROW3    LATCbits.LATC4
#define ROW4    LATGbits.LATG6
#define COL1    PORTCbits.RC3
#define COL2    PORTGbits.RG7
#define COL3    PORTGbits.RG8
#define COL4    PORTGbits.RG9


static void ShowMainMenu(void);
static void InitGame(void);


//------------------------------------------------------------------------------
// Simple Delays
//------------------------------------------------------------------------------
static void Delay_us(unsigned int us){
    unsigned int start = _CP0_GET_COUNT();
    unsigned int wait  = (SYS_FREQ/2/1000000)*us;
    while((_CP0_GET_COUNT() - start) < wait){}
}

static void Delay_ms(unsigned int ms){
    while(ms--){
        Delay_us(1000);
    }
}

//------------------------------------------------------------------------------
// LCD Functions
//------------------------------------------------------------------------------
void LCD_Command(uint8_t cmd){
    LCD_RS=0; LCD_RW=0; LCD_DATA=cmd;
    LCD_EN=1; Delay_us(50); LCD_EN=0;
    Delay_ms(2);
}

void LCD_Data(uint8_t d){
    LCD_RS=1; LCD_RW=0; LCD_DATA=d;
    LCD_EN=1; Delay_us(50); LCD_EN=0;
    Delay_us(50);
}

void LCD_Init(void){
    LCD_DATA_TRIS &= 0xFF00; // RE0..RE7 outputs
    LCD_RS_TRIS=0; LCD_RW_TRIS=0; LCD_EN_TRIS=0;
    Delay_ms(20);
    LCD_Command(0x38); Delay_ms(5);
    LCD_Command(0x0C); Delay_ms(5);
    LCD_Command(0x06); Delay_ms(5);
    LCD_Command(0x01); Delay_ms(5);
}

void LCD_Clear(void){
    LCD_Command(0x01);
    Delay_ms(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col){
    LCD_Command(0x80 | ((row?0x40:0)+col));
}

void LCD_String(const char* s){
    while(*s){
        LCD_Data(*s++);
    }
}

//------------------------------------------------------------------------------
// Timer3 ISR: Square wave if soundEnabled=1, else silence
//------------------------------------------------------------------------------
void __ISR(_TIMER_3_VECTOR, IPL5SOFT) T3InterruptHandler(void) {
    if (soundEnabled) {
        OC1RS = PR3 / 2; // 50% duty
    } else {
        OC1RS = 0;
    }
    IFS0bits.T3IF = 0; // clear interrupt flag
}


//------------------------------------------------------------------------------
// setFrequency: sets Timer3 so that the PWM is ~freq Hz
//------------------------------------------------------------------------------
static void setFrequency(unsigned int freq){
    if(freq<50) freq=50; // avoid extremely low
    T3CONbits.ON=0;
    TMR3=0;
    unsigned int prVal=(SYS_FREQ/(freq*2))-1;
    if(prVal>65535){
        T3CONbits.TCKPS=3; // 1:8
        prVal=((SYS_FREQ/8)/(freq*2))-1;
        if(prVal>65535) prVal=65535;
    } else {
        T3CONbits.TCKPS=0;
    }
    PR3=prVal;
    T3CONbits.ON=1;
}

//------------------------------------------------------------------------------
// PlayMelody: block while playing each note
//------------------------------------------------------------------------------
static void PlayMelody(const unsigned int *notes, const unsigned int *durations, int length){
    for(int i=0; i<length; i++){
        setFrequency(notes[i]);
        soundEnabled=1;
        Delay_ms(durations[i]);
        soundEnabled=0;
        Delay_ms(50);
    }
}

//------------------------------------------------------------------------------
// Example tunes
//------------------------------------------------------------------------------
static const unsigned int WIN_NOTES[]  = {523,659,784,1046};
static const unsigned int WIN_DURS[]   = {300,300,300,600};
static const int WIN_LEN=4;

static const unsigned int LOSE_NOTES[] = {392,330,262};
static const unsigned int LOSE_DURS[]  = {300,300,600};
static const int LOSE_LEN=3;

static const unsigned int MOVE_NOTES[]    = {440};
static const unsigned int MOVE_DURS[]     = {50};
static const int MOVE_LEN=1;

static const unsigned int COLLECT_NOTES[] = {523};
static const unsigned int COLLECT_DURS[]  = {100};
static const int COLLECT_LEN=1;


// Example "menu melody": 4 notes that loop indefinitely
#define MENU_LEN 4
static const unsigned int MENU_NOTES[MENU_LEN]  = {262, 294, 330, 349};  // C4, D4, E4, F4
static const unsigned int MENU_DURS[MENU_LEN]   = {500, 500, 500, 500}; // 500ms each

// Globals to track where we are in the menu melody
static int  menuMelodyIndex  = 0; // which note
static int  menuMelodyTime   = 0; // remaining time (ms) for the current note
static int  isMenuPlaying    = 0; // 1 = melody active, 0 = off


static void UpdateMenuMelody(void) {
    // If we are supposed to be playing the menu melody...
    if (isMenuPlaying) {
        // If the current note has finished, go to the next one
        if (menuMelodyTime <= 0) {
            // Move to the next note in the array
            menuMelodyIndex++;
            if (menuMelodyIndex >= MENU_LEN) {
                menuMelodyIndex = 0; // loop back to first note
            }
            // Set frequency for the new note
            setFrequency(MENU_NOTES[menuMelodyIndex]);
            soundEnabled = 1;  // Turn on the square wave

            // Reset the note duration counter
            menuMelodyTime = MENU_DURS[menuMelodyIndex];
        } 
        else {
            // Still playing the current note => just decrement time left
            // (we do this after each loop delay)
            // e.g. if we do Delay_ms(100) in the loop, subtract 100 here.
            // Adjust to match your loop delay.
            menuMelodyTime -= 100;
        }
    } 
    else {
        // If not playing, ensure the sound is off
        soundEnabled = 0;
    }
}



//------------------------------------------------------------------------------
// EndGameMessage: show line1/line2, play melody, then halt
//------------------------------------------------------------------------------
static void EndGameMessage(const char *line1, const char *line2,
                           const unsigned int *notes, const unsigned int *durations, int length){
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_String(line1);
    LCD_SetCursor(1,0);
    LCD_String(line2);

    PlayMelody(notes, durations, length);

    Delay_ms(5000);
    InitGame();
    ShowMainMenu();
}

//------------------------------------------------------------------------------
// Stickman logic
//------------------------------------------------------------------------------

// Define stickman character frames
const char stickmanFrames[2][8] = {
    {0b00000, 0b00100, 0b01110, 0b00100, 0b01110, 0b10101, 0b00100, 0b00000}, // Frame 1
    {0b00000, 0b00100, 0b01110, 0b00100, 0b10101, 0b01110, 0b01010, 0b00000}  // Frame 2
};

static const char ballFrame[8] = {
    0b00000,
    0b00110,
    0b01111,
    0b01111,
    0b01111,
    0b00110,
    0b00000,
    0b00000
};

static const char chaserFrame[8] = {
    0b00000,
    0b11011,
    0b11111,
    0b10101,
    0b11111,
    0b11011,
    0b00000,
    0b00000
};


// Function to load custom characters
void LCD_LoadCustomChar(unsigned char location, const char *pattern) {
    LCD_Command(0x40 + (location << 3)); // Set CGRAM address
    for (int i = 0; i < 8; i++) {
        LCD_Data(pattern[i]);
    }
}

void animateStickman(int line) {
    LCD_Clear();
    LCD_SetCursor(0, 0);

    LCD_LoadCustomChar(0, stickmanFrames[0]); // Load first frame

    int prevPos = -1; // To track the previous position of the stickman
    for (int pos = 0; pos < 16; pos++) {
        // Clear the previous position if it exists
        if (prevPos >= 0) {
            LCD_SetCursor(line, prevPos);
            LCD_String(" "); // Overwrite with a space
        }

        // Update current position
        LCD_SetCursor(line, pos);
        LCD_Data(0); // Show the stickman

        prevPos = pos; // Update the previous position
        Delay_ms(300); // Pause
    }
}

void Stickman_Init(void) {
    // Load frame 0 (or 1, your choice) into CGRAM index 0
    LCD_LoadCustomChar(0, stickmanFrames[0]);
}



//------------------------------------------------------------------------------
// Keypad scanning
//------------------------------------------------------------------------------
static char keypad[4][4]={
    {'D','C','B','A'},
    {'E','9','6','3'},
    {'F','8','5','2'},
    {'0','7','4','1'}
};

static int CheckCols(int row){
    if(!PORTCbits.RC3)return (row<<4)|0;
    if(!PORTGbits.RG7)return (row<<4)|1;
    if(!PORTGbits.RG8)return (row<<4)|2;
    if(!PORTGbits.RG9)return (row<<4)|3;
    return -1;
}

static char Keypad_Scan(void){
    for(int r=0; r<4; r++){
        LATCbits.LATC2=1; LATCbits.LATC1=1; LATCbits.LATC4=1; LATGbits.LATG6=1;
        switch(r){
            case 0: LATCbits.LATC2=0;break;
            case 1: LATCbits.LATC1=0;break;
            case 2: LATCbits.LATC4=0;break;
            case 3: LATGbits.LATG6=0;break;
        }
        Delay_us(200);
        int c=CheckCols(r);
        if(c>=0){
            Delay_ms(50);
            if(CheckCols(r)==c){
                int rr=(c>>4), cc=(c&0xF);
                return keypad[rr][cc];
            }
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
// Game Variables
//------------------------------------------------------------------------------
char grid[LCD_ROWS][LCD_COLS];
int player_x=0, player_y=0;
int ball_x=5, ball_y=0;
int chaser_x=15, chaser_y=1;
int score=0;

// For timed chaser movement
int chaserTimer=0; 
int chaserMoveInterval=1500; // default for normal mode

//------------------------------------------------------------------------------
// Functions to update/draw the grid
//------------------------------------------------------------------------------
void update_grid(void){
    for(int row=0; row<LCD_ROWS; row++){
        for(int col=0; col<LCD_COLS; col++){
            grid[row][col] = ' ';
        }
    }
    grid[player_y][player_x] = 0;
    grid[ball_y][ball_x]     = 1;
    grid[chaser_y][chaser_x] = 2;
}

void draw_grid(void){
    LCD_Clear();
    for(int row=0; row<LCD_ROWS; row++){
        LCD_SetCursor(row,0);
        for(int col=0; col<LCD_COLS; col++){
            LCD_Data(grid[row][col]);
        }
    }
}

// Move the chaser
void move_chaser(void){
    if(chaser_x>player_x) chaser_x--;
    else if(chaser_x<player_x) chaser_x++;
    if(chaser_y>player_y) chaser_y--;
    else if(chaser_y<player_y) chaser_y++;
}

// Check collisions
void check_collision(void){
    // Player collects ball
    if(player_x==ball_x && player_y==ball_y){
        score++;
        ball_x=rand()%LCD_COLS;
        ball_y=rand()%LCD_ROWS;

        if(score<3){
            PlayMelody(COLLECT_NOTES, COLLECT_DURS, COLLECT_LEN);
        } else {
            char buf[16];
            sprintf(buf,"Score: %d", score);
            EndGameMessage("YOU WIN!", buf, WIN_NOTES, WIN_DURS, WIN_LEN);
        }
    }
    // Chaser catches player => game over
    if(player_x==chaser_x && player_y==chaser_y){
        char buf[16];
        sprintf(buf,"Score: %d", score);
        EndGameMessage("Game Over!", buf, LOSE_NOTES, LOSE_DURS, LOSE_LEN);
        
    }
}

//------------------------------------------------------------------------------
// New: Initialize or Reset the Game
//------------------------------------------------------------------------------
static void InitGame(void){
    // Reset positions and score
    player_x=0; player_y=0;
    ball_x=5;   ball_y=0;
    chaser_x=15; chaser_y=1;
    score=0;
    chaserTimer=0;
    // If SW1 is read right now, we can set the speed:
    if(SW1==1){
        chaserMoveInterval=500;  // Hard mode
    } else {
        chaserMoveInterval=1500; // Normal mode
    }
    update_grid();
    draw_grid();
}

//------------------------------------------------------------------------------
// New: Show Main Menu
//   - Wait for keypad: '1' => Start new game, '2' => Exit
//------------------------------------------------------------------------------
static void ShowMainMenu(void) {
    LCD_Clear();
    LCD_String("1. Start New Game");
    LCD_SetCursor(1,0);
    LCD_String("2. Exit");

    // Set up the melody to start from the beginning
    isMenuPlaying = 1;        // turn on background music
    menuMelodyIndex = 0;
    menuMelodyTime  = 0;      // force immediate load of the first note

    while (1) {
        // Let the melody update in the background
        

        //Play melody only if SW3 is set to 1
        if(SW3 == 1){
            isMenuPlaying = 1;
            UpdateMenuMelody();
        }
        else{
            isMenuPlaying = 0;
            soundEnabled = 0;
            
            //Return melody to start
            menuMelodyIndex = 0;
            menuMelodyTime  = 0;
        }
        
        // Example: your Keypad_Scan
        char k = Keypad_Scan();

        // If user pressed '1' => start new game
        if (k == '1') {
            // Stop the melody
            isMenuPlaying = 0;
            soundEnabled  = 0;
            LCD_Clear();
            LCD_String("Starting...");
            Delay_ms(500); 
            return; // exit this function => go run the game
        }
        // If user pressed '2' => exit
        else if (k == '2') {
            // Stop the melody
            isMenuPlaying = 0;
            soundEnabled  = 0;
            LCD_Clear();
            LCD_String("Exiting...");
            while(1) {
                // stuck here
            }
        }

        // ~100 ms loop delay => matches the time we subtract in UpdateMenuMelody
        Delay_ms(100);
    }
}


//------------------------------------------------------------------------------
// Setup
//------------------------------------------------------------------------------
static void setup(void){
    // Keypad outputs
    TRISCbits.TRISC2=0; TRISCbits.TRISC1=0; TRISCbits.TRISC4=0; TRISGbits.TRISG6=0;
    LATCbits.LATC2=1;   LATCbits.LATC1=1;   LATCbits.LATC4=1;   LATGbits.LATG6=1;

    // Keypad inputs
    TRISCbits.TRISC3=1; TRISGbits.TRISG7=1; TRISGbits.TRISG8=1; TRISGbits.TRISG9=1;
    ANSELGbits.ANSG7=0; ANSELGbits.ANSG8=0; ANSELGbits.ANSG9=0;
    CNPUCbits.CNPUC3=1; CNPUGbits.CNPUG7=1; CNPUGbits.CNPUG8=1; CNPUGbits.CNPUG9=1;

    // Timer3 + OC1
    TRISBbits.TRISB14=0; ANSELBbits.ANSB14=0; RPB14R=0x0C;
    T3CON=0; TMR3=0; PR3=5000; T3CONbits.TCKPS=0; T3CONbits.ON=1;
    OC1CON=0; OC1R=0; OC1RS=0; OC1CONbits.OCM=0b110; OC1CONbits.OCTSEL=1; OC1CONbits.ON=1;
    IPC3bits.T3IP=5; IFS0bits.T3IF=0; IEC0bits.T3IE=1;

    // LCD
    LCD_Init();

    // LEDs on A (optional)
    TRISAbits.TRISA0=0; TRISAbits.TRISA1=0; 
    TRISAbits.TRISA2=0; TRISAbits.TRISA3=0;
    TRISAbits.TRISA4=0; TRISAbits.TRISA5=0; 
    TRISAbits.TRISA6=0; TRISAbits.TRISA7=0;
    LATA=0;

    // Switch inputs
    TRISBbits.TRISB0=1; // SW0
    TRISBbits.TRISB1=1; // SW1
    TRISBbits.TRISB2=1; // SW2
    TRISBbits.TRISB3=1; // SW3
    
    // Optionally enable internal pull-ups if needed:
    // CNPUBbits.CNPUB0=1; CNPUBbits.CNPUB1=1; CNPUBbits.CNPUB2=1;

    // Multi-vector
    INTCONbits.MVEC=1;
    __builtin_enable_interrupts();
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main(void){
    setup();

    // Show the main menu initially
    ShowMainMenu();

    // At this point, the user has chosen "Start New Game," so game is initialized
    LCD_Clear();
    LCD_String("Stickman Game");
    
    
    // Load characters frames
    LCD_LoadCustomChar(0, stickmanFrames[0]);
    LCD_LoadCustomChar(1, ballFrame);
    LCD_LoadCustomChar(2, chaserFrame);
    
    Delay_ms(1000);

    // By default, we re-init here (just in case)
    InitGame();

    // Main loop
    char last_key=0;
    while(1){
        // 1) Check SW0: return to main menu if pressed
        if(SW0==0){
            ShowMainMenu();  // If user returns from menu with '1', we keep going
        }

        // 2) Check SW2: if pressed => restart game
        if(SW2==1){
            InitGame();
        }

        // 3) Check SW1 at any time => adjust speed mid-game (optional)
        //    If you want the mode to change "live":
        if(SW1==1){
            chaserMoveInterval=500;  // Hard
        } else {
            chaserMoveInterval=1500; // Normal
        }

        
        // Keypad input
        char key=Keypad_Scan();
        if(key && key!=last_key){
            last_key=key;
            int old_x=player_x, old_y=player_y;

            // Move logic
            if(key=='4' && player_y>0){
                player_y--;
            } else if(key=='6' && player_y<(LCD_ROWS-1)){
                player_y++;
            } else if(key=='8'){
                player_x--;
                if(player_x<0) player_x=LCD_COLS-1;
            } else if(key=='2'){
                player_x++;
                if(player_x>=LCD_COLS) player_x=0;
            }

            // If moved => short beep
            if(player_x!=old_x || player_y!=old_y){
                PlayMelody(MOVE_NOTES, MOVE_DURS, MOVE_LEN);
            }

            update_grid();
            draw_grid();
            check_collision();
        }
        if(!key){
            last_key=0;
        }

        // Delay 100ms, then increment chaserTimer
        Delay_ms(100);
        chaserTimer+=100;

        // If time to move chaser
        if(chaserTimer>=chaserMoveInterval){
            move_chaser();
            update_grid();
            draw_grid();
            check_collision();
            chaserTimer=0; // reset
        }
    }
}
