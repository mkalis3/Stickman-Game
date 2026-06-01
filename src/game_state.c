#include "../include/game_state.h"

static GameResult make_result(const GameState *state, int events)
{
    GameResult result;
    result.events = events;
    result.score = state->score;
    return result;
}

static void place_ball(GameState *state, GameRandomFn random_fn)
{
    if (random_fn == 0) {
        state->ball_x = 5;
        state->ball_y = 0;
        return;
    }

    state->ball_x = (int)random_fn(GAME_COLS);
    state->ball_y = (int)random_fn(GAME_ROWS);
}

static void move_chaser(GameState *state)
{
    if (state->chaser_x > state->player_x) {
        state->chaser_x--;
    } else if (state->chaser_x < state->player_x) {
        state->chaser_x++;
    }

    if (state->chaser_y > state->player_y) {
        state->chaser_y--;
    } else if (state->chaser_y < state->player_y) {
        state->chaser_y++;
    }
}

static GameResult evaluate_collisions(GameState *state, int events, GameRandomFn random_fn)
{
    if (state->player_x == state->ball_x && state->player_y == state->ball_y) {
        state->score++;
        events |= GAME_EVENT_BALL_COLLECTED;

        if (state->score >= GAME_TARGET_SCORE) {
            events |= GAME_EVENT_WON;
            return make_result(state, events);
        }

        place_ball(state, random_fn);
    }

    if (state->player_x == state->chaser_x && state->player_y == state->chaser_y) {
        events |= GAME_EVENT_LOST;
    }

    return make_result(state, events);
}

void game_state_reset(GameState *state, GameDifficulty difficulty)
{
    state->player_x = 0;
    state->player_y = 0;
    state->ball_x = 5;
    state->ball_y = 0;
    state->chaser_x = 15;
    state->chaser_y = 1;
    state->score = 0;
    state->chaser_timer_ms = 0;
    game_state_set_difficulty(state, difficulty);
}

void game_state_set_difficulty(GameState *state, GameDifficulty difficulty)
{
    state->chaser_move_interval_ms = difficulty == GAME_DIFFICULTY_HARD
        ? GAME_HARD_CHASER_INTERVAL_MS
        : GAME_NORMAL_CHASER_INTERVAL_MS;
}

GameInput game_input_from_key(char key)
{
    switch (key) {
        case '4':
            return GAME_INPUT_UP;
        case '6':
            return GAME_INPUT_DOWN;
        case '8':
            return GAME_INPUT_LEFT;
        case '2':
            return GAME_INPUT_RIGHT;
        default:
            return GAME_INPUT_NONE;
    }
}

GameResult game_state_apply_input(GameState *state, GameInput input, GameRandomFn random_fn)
{
    int original_x = state->player_x;
    int original_y = state->player_y;

    switch (input) {
        case GAME_INPUT_UP:
            if (state->player_y > 0) {
                state->player_y--;
            }
            break;
        case GAME_INPUT_DOWN:
            if (state->player_y < GAME_ROWS - 1) {
                state->player_y++;
            }
            break;
        case GAME_INPUT_LEFT:
            state->player_x--;
            if (state->player_x < 0) {
                state->player_x = GAME_COLS - 1;
            }
            break;
        case GAME_INPUT_RIGHT:
            state->player_x++;
            if (state->player_x >= GAME_COLS) {
                state->player_x = 0;
            }
            break;
        default:
            break;
    }

    int events = state->player_x != original_x || state->player_y != original_y
        ? GAME_EVENT_PLAYER_MOVED
        : GAME_EVENT_NONE;

    return evaluate_collisions(state, events, random_fn);
}

GameResult game_state_tick(GameState *state, int elapsed_ms)
{
    state->chaser_timer_ms += elapsed_ms;
    if (state->chaser_timer_ms < state->chaser_move_interval_ms) {
        return make_result(state, GAME_EVENT_NONE);
    }

    state->chaser_timer_ms = 0;
    move_chaser(state);
    return evaluate_collisions(state, GAME_EVENT_CHASER_MOVED, 0);
}

void game_state_render(const GameState *state, char grid[GAME_ROWS][GAME_COLS])
{
    for (int row = 0; row < GAME_ROWS; row++) {
        for (int col = 0; col < GAME_COLS; col++) {
            grid[row][col] = ' ';
        }
    }

    grid[state->player_y][state->player_x] = 0;
    grid[state->ball_y][state->ball_x] = 1;
    grid[state->chaser_y][state->chaser_x] = 2;
}
