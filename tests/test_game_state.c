#include <assert.h>
#include <stdio.h>

#include "../include/game_state.h"

static unsigned int random_values[] = {7, 1, 3, 0};
static unsigned int random_index = 0;

static unsigned int deterministic_random(unsigned int upper_bound)
{
    unsigned int value = random_values[random_index++];
    return upper_bound == 0U ? 0U : value % upper_bound;
}

static void reset_random(void)
{
    random_index = 0;
}

static void reset_sets_initial_positions_and_difficulty(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_HARD);

    assert(state.player_x == 0);
    assert(state.player_y == 0);
    assert(state.ball_x == 5);
    assert(state.ball_y == 0);
    assert(state.chaser_x == 15);
    assert(state.chaser_y == 1);
    assert(state.score == 0);
    assert(state.chaser_move_interval_ms == GAME_HARD_CHASER_INTERVAL_MS);
}

static void horizontal_movement_wraps_around_lcd_edges(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_NORMAL);

    GameResult result = game_state_apply_input(&state, GAME_INPUT_LEFT, deterministic_random);
    assert((result.events & GAME_EVENT_PLAYER_MOVED) != 0);
    assert(state.player_x == GAME_COLS - 1);

    result = game_state_apply_input(&state, GAME_INPUT_RIGHT, deterministic_random);
    assert((result.events & GAME_EVENT_PLAYER_MOVED) != 0);
    assert(state.player_x == 0);
}

static void vertical_movement_stays_inside_two_rows(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_NORMAL);

    GameResult result = game_state_apply_input(&state, GAME_INPUT_UP, deterministic_random);
    assert(result.events == GAME_EVENT_NONE);
    assert(state.player_y == 0);

    result = game_state_apply_input(&state, GAME_INPUT_DOWN, deterministic_random);
    assert((result.events & GAME_EVENT_PLAYER_MOVED) != 0);
    assert(state.player_y == 1);
}

static void collecting_ball_increments_score_and_repositions_ball(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_NORMAL);
    state.player_x = 4;
    state.player_y = 0;
    reset_random();

    GameResult result = game_state_apply_input(&state, GAME_INPUT_RIGHT, deterministic_random);

    assert((result.events & GAME_EVENT_BALL_COLLECTED) != 0);
    assert(state.score == 1);
    assert(state.ball_x == 7);
    assert(state.ball_y == 1);
}

static void third_ball_collect_sets_win_event(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_NORMAL);
    state.player_x = 4;
    state.player_y = 0;
    state.score = GAME_TARGET_SCORE - 1;

    GameResult result = game_state_apply_input(&state, GAME_INPUT_RIGHT, deterministic_random);

    assert((result.events & GAME_EVENT_WON) != 0);
    assert(result.score == GAME_TARGET_SCORE);
}

static void chaser_moves_after_interval_and_can_catch_player(void)
{
    GameState state;
    game_state_reset(&state, GAME_DIFFICULTY_HARD);
    state.player_x = 14;
    state.player_y = 1;

    GameResult result = game_state_tick(&state, GAME_HARD_CHASER_INTERVAL_MS - 1);
    assert(result.events == GAME_EVENT_NONE);
    assert(state.chaser_x == 15);

    result = game_state_tick(&state, 1);
    assert((result.events & GAME_EVENT_CHASER_MOVED) != 0);
    assert((result.events & GAME_EVENT_LOST) != 0);
    assert(state.chaser_x == 14);
}

static void render_places_all_entities_in_grid(void)
{
    GameState state;
    char grid[GAME_ROWS][GAME_COLS];
    game_state_reset(&state, GAME_DIFFICULTY_NORMAL);
    game_state_render(&state, grid);

    assert(grid[0][0] == 0);
    assert(grid[0][5] == 1);
    assert(grid[1][15] == 2);
}

int main(void)
{
    reset_sets_initial_positions_and_difficulty();
    horizontal_movement_wraps_around_lcd_edges();
    vertical_movement_stays_inside_two_rows();
    collecting_ball_increments_score_and_repositions_ball();
    third_ball_collect_sets_win_event();
    chaser_moves_after_interval_and_can_catch_player();
    render_places_all_entities_in_grid();

    puts("game_state tests passed");
    return 0;
}
