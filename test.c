#include "mumble.h"

#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char identity[256];
static struct MumbleContext* context = NULL;

static void create_mumble_context(void) {
	mumble_destroy_context(&context);

	context = mumble_create_context_args("MumbleLinkTest", "Test of https://github.com/SollyBunny/mumble-link-c");
	if (!context) {
		perror("mumble_create_context");
		exit(1);
	}

	if (!mumble_set_context(context, "EVERYONE")) {
		fprintf(stderr, "Failed to set context\n");
		mumble_destroy_context(&context);
		exit(1);
	}

	if (!mumble_set_identity(context, identity)) {
		fprintf(stderr, "Failed to set identity\n");
		mumble_destroy_context(&context);
		exit(1);
	}
}

int main(void) {
	setlocale(LC_ALL, "");
	srand((unsigned int)time(NULL));

	printf("Enter your name: ");
	if (!fgets(identity, sizeof(identity), stdin)) {
		fprintf(stderr, "Failed to read input\n");
		return 1;
	}
	identity[strcspn(identity, "\n")] = '\0';

	create_mumble_context();
	mumble_2d_update(context, (float)(rand() % 10), (float)(rand() % 10));

	while (true) {
		printf("\n");

		if (mumble_relink_needed(context)) {
			create_mumble_context();
			printf("Relinked!\n");
		}

		struct MumbleLinkedMem* lm = mumble_get_linked_mem(context);
		printf("Identity: \"%ls\" X: %f Y: %f\n", lm->identity, lm->fCameraPosition[0], lm->fCameraPosition[2]);

		printf("Exit: exit\n");
		printf("Set position: %%d,%%d (eg. 6,7)\n");
		printf("Enter command: ");
		char input[256];
		if (!fgets(input, sizeof(input), stdin)) {
			fprintf(stderr, "Failed to read input\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';

		float x, y;
		if (strcmp(input, "exit") == 0) {
			break;
		} else if (sscanf(input, "%f,%f", &x, &y) == 2) {
			mumble_2d_update(context, x, y);
		} else if (input[0] != '\0') {
			printf("Unknown command\n");
		}
	}

	mumble_destroy_context(&context);

	return 0;
}
