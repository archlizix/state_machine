#include "fsm.h"
#include <stdlib.h>
#include <stdio.h>

/*!
    \brief To support multiple instances, this function must be stateless.
*/
int transfer(struct StateMachine *fsm, struct Event *event)
{
	if (fsm->cur_state->updater == NULL) {
		return -1;
	}

	if (fsm->cur_state->updater(fsm, event) == false) {
		return 0;
	}

	fsm->cur_state->exit_action(fsm, event);
	fsm->pre_state = fsm->cur_state;
	fsm->cur_state = fsm->nxt_state;
	fsm->nxt_state = NULL;

	fsm->cur_state->entry_action(fsm, event);
	return 0;
}

struct StateMachine *new_fsm(struct State *state_initial)
{
	struct StateMachine *fsm =
		(struct StateMachine *)malloc(sizeof(struct StateMachine));
	if (!fsm) {
		return NULL;
	}

	fsm->pre_state = NULL;
	fsm->cur_state = state_initial;
	fsm->nxt_state = NULL;
	fsm->transfer = transfer;
	return fsm;
}

int delete_fsm(struct StateMachine *fsm)
{
	free(fsm);
	fsm = NULL;
	return 0;
}

struct State *get_previous_state(struct StateMachine *fsm)
{
	if (!fsm) {
		return NULL;
	}

	return fsm->pre_state;
}

struct State *get_current_state(struct StateMachine *fsm)
{
	if (!fsm) {
		return NULL;
	}

	return fsm->cur_state;
}

struct State *get_next_state(struct StateMachine *fsm)
{
	if (!fsm) {
		return NULL;
	}

	return fsm->nxt_state;
}
