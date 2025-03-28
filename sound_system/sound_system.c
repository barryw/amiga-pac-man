//
// Created by Barry Walker on 3/27/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <clib/dos_protos.h>
#include <proto/dos.h>

#include "sound_manager.h"
#include "credit.h"
#include "intermission.h"
#include "intromusic.h"


int main() {
    init_sound_manager();

    printf("Press a key between 1 and 3 to play a sound (0 to quit)\n");

    BOOL cont = TRUE;

    while (cont) {
        WaitForChar(Input(), -1);
        const LONG key = FGetC(Input());

        switch (key) {
            case '0':
                cont = FALSE;
                break;
            case '1':
                play_sound(credit_raw, credit_raw_len, 11025, FALSE, 10, DEFAULT_VOLUME);
                break;
            case '2':
                play_sound(intermission_raw, intermission_raw_len, 11025, TRUE, 10, 10);
                break;
            case '3':
                play_sound(pacintro_raw, pacintro_raw_len, 11025, FALSE, 10, DEFAULT_VOLUME);
                break;
            default:
                printf("What is ya, idnorant?\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}
