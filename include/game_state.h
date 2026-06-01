#ifndef GAME_STATE_H
#define GAME_STATE_H

#define GAME_ROWS 2
#define GAME_COLS 16
#define GAME_TARGET_SCORE 3
#define GAME_NORMAL_CHASER_INTERVAL_MS 1500
#define GAME_HARD_CHASER_INTERVAL_MS 500

typedef enum {
    GAME_DIFFICULTY_NORMAL = 0,
    GAME_DIFFICULTY_HARD = 1
} GameDifficulty;

typedef enum {
    GAME_INPUT_NONE = 0,
    GAME_INPUT_UP,
    GAME_INPUT_DOWN,
    GAME_INPUT_LEFT,
    GAME_INPUT_RIGHT
} GameInput;

typedef enum {
    GAME_EVENT_NONE = 0,
    GAME_EVENT_PLAYER_MOVED = 1 << 0,
    GAME_EVENT_BALL_COLLECTED = 1 << 1,
    GAME_EVENT_WON = 1 << 2,
    GAME_EVENT_LOST = 1 << 3,
    GAME_EVENT_CHASER_MOVED = 1 << 4
} GameEvent;

typedef struct {
    int player_x;
    int player_y;
    int ball_x;
    int ball_y;
    int chaser_x;
    int chaser_y;
    int score;
    int chaser_timer_ms;
    int chaser_move_interval_ms;
} GameState;

typedef struct {
    int events;
    int score;
} GameResult;

typedef unsigned int (*GameRandomFn)(unsigned int upper_bound);

void game_state_reset(GameState *state, GameDifficulty difficulty);
void game_state_set_difficulty(GameState *state, GameDifficulty difficulty);
GameInput game_input_from_key(char key);
GameResult game_state_apply_input(GameState *state, GameInput input, GameRandomFn random_fn);
GameResult game_state_tick(GameState *state, int elapsed_ms);
void game_state_render(const GameState *state, char grid[GAME_ROWS][GAME_COLS]);

#endif
