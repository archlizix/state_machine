#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fsm.h"

static bool captured_10_event(struct StateMachine *fsm, struct Event *event);
static void print_state_id(struct StateMachine *fsm, struct Event *event);

struct Event event_0 = {
	.id = 0,
	.data = 0,
};

struct Event event_1 = {
	.id = 1,
	.data = 0,
};

struct State state_error = {
	.id = -1,
	.data = 0,
	.updater = NULL,
	.entry_action = print_state_id,
	.exit_action = NULL,
};

struct State state_0 = {
	.id = 0,
	.data = 0,
	.updater = captured_10_event,
	.entry_action = print_state_id,
	.exit_action = NULL,
};

struct State state_1 = {
	.id = 1,
	.data = 0,
	.updater = NULL,
	.entry_action = print_state_id,
	.exit_action = NULL,
};

struct State state_end = {
	.id = 100,
	.data = 0,
	.updater = NULL,
	.entry_action = print_state_id,
	.exit_action = NULL,
};

int main(void)
{
	struct StateMachine *foo = new_fsm(&state_0);
	if (!foo) {
		return -1;
	}

	while (foo->cur_state != &state_end) {
		(foo->transfer)(foo, &event_0);
	}

	delete_fsm(foo);

	return 0;
}

/*!
    \brief need to set state->data to zero in entry_action() TODO: or in transfer
*/
static bool captured_10_event(struct StateMachine *fsm, struct Event *event)
{
	if (event == &event_0) {
		++(fsm->cur_state->data);
		printf("Captured event_0 %d time(s).\n", fsm->cur_state->data);
	}

	if (fsm->cur_state->data >= 10) {
		fsm->nxt_state = &state_end;
		return true;
	}
	return false;
}

static void print_state_id(struct StateMachine *fsm, struct Event *event)
{
	printf("Current state id is %d.\n", fsm->cur_state->id);
}
