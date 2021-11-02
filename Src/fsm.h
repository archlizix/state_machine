#pragma once

#include <stdint.h>
#include <stdbool.h>

struct StateMachine;

struct Event {
	int id;
	intptr_t data; //It could even be a pointer.
};

struct State {
	int id;
	intptr_t data; //It could even be a pointer.
	bool (* updater)(struct StateMachine *fsm, struct Event *event);
	void (* entry_action)(struct StateMachine *fsm, struct Event *event);
	void (* exit_action)(struct StateMachine *fsm, struct Event *event);
};

struct StateMachine {
	struct State *pre_state;
	struct State *cur_state;
	struct State *nxt_state;
	int (* transfer)(struct StateMachine *fsm, struct Event *event);
};

struct StateMachine *new_fsm(struct State *state_initial);
int free_fsm(struct StateMachine *fsm);
struct State *get_current_state(struct StateMachine *fsm);
struct State *get_previous_state(struct StateMachine *fsm);
struct State *get_next_state(struct StateMachine *fsm);

#define delete_fsm(x) free_fsm(x);\
	x = NULL;
