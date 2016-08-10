#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "poker.h"

/* converts a hand (of 5 cards) to a string representation, and stores it in the
 * provided buffer. The buffer is assumed to be large enough.
 */
void hand_to_string (hand_t hand, char *handstr) {
    char *p = handstr;
    int i;
    char *val, *suit;
    for (i=0; i<5; i++) {
	if (hand[i].value < 10) {
	    *p++ = hand[i].value + '0';
	} else {
	    switch(hand[i].value) {
		case 10: *p++ = 'T'; break;
		case 11: *p++ = 'J'; break;
		case 12: *p++ = 'Q'; break;
		case 13: *p++ = 'K'; break;
		case 14: *p++ = 'A'; break;
	    }
	}
	switch(hand[i].suit) {
	    case DIAMOND: *p++ = 'D'; break;
	    case CLUB: *p++ = 'C'; break;
	    case HEART: *p++ = 'H'; break;
	    case SPADE: *p++ = 'S'; break;
	}
	if (i<=3) *p++ = ' ';
    }
    *p = '\0';
}

/* converts a string representation of a hand into 5 separate card structs. The
 * given array of cards is populated with the card values.
 */
void string_to_hand (const char *handstr, hand_t hand) {
    const char *p = handstr;
    int i;
    int val;
    int suit;
    //Make 5 separate card structs
    for ( i = 0; i < 5; i++ ){
	//Corresponding ASCII char value to int
	switch(*p){
	    case 'T': hand[i].value = 10; break;
	    case 'J': hand[i].value = 11; break;
	    case 'Q': hand[i].value = 12; break;
	    case 'K': hand[i].value = 13; break;
	    case 'A': hand[i].value = 14; break;
	    default: hand[i].value = *p - '0'; break;
	}
	*p++;
	switch ( *p++ ){
	    //Corresponding ASCII char value to an int from 0 to 3
	    //Corresponds to enum {Diamond, Club, Heart, Spade}
	    case 'D': hand[i].suit = DIAMOND; break;
	    case 'C': hand[i].suit = CLUB; break;
	    case 'H': hand[i].suit = HEART; break;
	    case 'S': hand[i].suit = SPADE; break;
	    default: printf("ERROR\n"); break;
	}
	*p++;
    }
}

/* sorts the hands so that the cards are in ascending order of value (two
 * lowest, ace highest */
void sort_hand (hand_t hand) {
    //Using Selection Sort
    int i, j;
    for( i = 0; i <= 3; i++ ){
	for( j = 1 + i; j <= 4; j++ ){
	    if( hand[i].value > hand[j].value ){
		card_t temp = hand[i];	//Temp storage for swap.
		hand[i] = hand[j];
		hand[j] = temp;
	    }
	}
    }
}
//I don't use this function
int count_pairs (hand_t hand) {
    sort_hand(hand);
    return 0;
}

//Checks for pair
int is_onepair (hand_t hand) {
    sort_hand(hand);
    int i;
    for ( i = 0; i < 4; i++ ){
	if ( hand[i].value == hand[i + 1].value ){
	    return 1;
	}
    }
    return 0;
}

int is_twopairs (hand_t hand) {
    sort_hand(hand);
    if( ( ( hand[0].value == hand[1].value ) && ( hand[2].value == hand[3].value ) )
	    || ( ( hand[1].value == hand[2].value ) && ( hand[3].value == hand[4].value ) )
	    || ( ( hand[0].value == hand[1].value ) && ( hand[3].value == hand[4].value ) ) ){
	return 1;
    }
    return 0;
}

int is_threeofakind (hand_t hand) {
    sort_hand(hand);
    int i;
    for ( i = 0; i < 3; i++ ){
	if( ( hand[i].value == hand[i + 1].value ) && ( hand[i + 1].value == hand[i + 2].value ) ){
	    return 1;
	}
    }
    return 0;
}

int is_straight (hand_t hand) {
    sort_hand(hand);
    if( ( ( hand[0].value + 1 ) == hand[1].value ) && ( ( hand[1].value + 1 ) == hand[2].value ) && ( ( hand[2].value + 1 ) == hand[3].value ) && ( ( hand[3].value + 1 ) == hand[4].value )){
	return 1;
    }
    //if the first card is 2 and the last card is ace.
    //treats the ace as a one
    if( ( hand[0].value == 2 ) && ( hand[4].value == 14 ) ){
	if( ( ( hand[0].value + 1 ) == hand[1].value ) && ( ( hand[1].value + 1 ) == hand[2].value ) && ( ( hand[2].value + 1 ) == hand[3].value ) ){
	    return 1;
	}
    }

    return 0;
}

int is_fullhouse (hand_t hand) {
    sort_hand(hand);
    if( ( ( hand[0].value == hand[1].value ) && ( hand[1].value == hand[2].value ) ) && ( hand[3].value == hand[4].value ) ){
	return 1;
    }
    if( ( hand[0].value == hand[1].value ) && ( ( hand[2].value == hand[3].value ) && ( hand[3].value == hand[4].value ) ) ){
	return 1;
    }
    return 0;
}

int is_flush (hand_t hand) {
    sort_hand(hand);
    if( ( hand[0].suit == hand[1].suit ) && ( hand[1].suit == hand[2].suit ) && ( hand[2].suit == hand[3].suit ) && ( hand[3].suit == hand[4].suit )){
	return 1;
    }
    return 0;
}

int is_straightflush (hand_t hand) {
    sort_hand(hand);
    if ( ( is_straight(hand) ) && ( is_flush(hand) ) ){
	return 1;
    }
    return 0;
}

int is_fourofakind (hand_t hand) {
    sort_hand(hand);
    if( ( ( hand[0].value == hand[1].value ) && ( hand[1].value == hand[2].value ) && ( hand[2].value == hand[3].value ) )
	    || ( ( hand[1].value == hand[2].value ) && ( hand[2].value == hand[3].value ) && (hand[3].value == hand[4].value ) ) ){
	return 1;
    }
    return 0;
}

int is_royalflush (hand_t hand) {
    sort_hand(hand);
    if( hand[0].value == 10){
	if( ( is_straight(hand) ) && ( is_flush(hand) ) ){
	    return 1;
	}
    }
    return 0;
}

/* compares the hands based on rank -- if the ranks (and rank values) are
 * identical, compares the hands based on their highcards.
 * returns 0 if h1 > h2, 1 if h2 > h1.
 */
int compare_hands (hand_t h1, hand_t h2) {
    sort_hand(h1);
    sort_hand(h2);
    if( ( is_royalflush(h1) ) && !( is_royalflush(h2) ) ){
	return 0;
    }else if( ( is_royalflush(h2) ) && !( is_royalflush(h1) ) ){
	return 1;
    }else if( ( is_straightflush(h1) ) && !( is_straightflush(h2) ) ){
	return 0;
    }else if( ( is_straightflush(h2) ) && !( is_straightflush(h1) ) ){
	return 1;
    }else if( ( is_straightflush(h1) ) && ( is_straightflush(h2) ) ){
	return compare_highcards(h1, h2);
    }else if( ( is_fourofakind(h1) ) && !( is_fourofakind(h2) ) ){
	return 0;
    }else if( ( is_fourofakind(h2) ) && !( is_fourofakind(h1) ) ){
	return 1;
    }else if( ( is_fourofakind(h1) ) && ( is_fourofakind(h2) ) ){
	return fourofakind_check(h1, h2);
    }else if( ( is_fullhouse(h1) ) && !( is_fullhouse(h2) ) ){
	return 0;
    }else if( ( is_fullhouse(h2) ) && !( is_fullhouse(h1) ) ){
	return 1;
    }else if( ( is_fullhouse(h1) ) && ( is_fullhouse(h2) ) ){
	return threeofakind_check(h1, h2);//threeofakind_check should work with a fullhouse.
    }else if( ( is_flush(h1) ) && !( is_flush(h2) ) ){
	return 0;
    }else if( ( is_flush(h2) ) && !( is_flush(h1) ) ){
	return 1;
    }else if( ( is_flush(h1) ) && ( is_flush(h2) ) ){
	return compare_highcards(h1, h2);
    }else if( ( is_straight(h1) ) && !( is_straight(h2) ) ){
	return 0;
    }else if( ( is_straight(h2) ) && !( is_straight(h1) ) ){
	return 1;
    }else if( ( is_straight(h1) ) && (is_straight(h2) ) ){
	return compare_highcards(h1, h2);
    }else if( ( is_threeofakind(h1) ) && !( is_threeofakind(h2) ) ){
	return 0;
    }else if( ( is_threeofakind(h2) ) && !( is_threeofakind(h1) ) ){
	return 1;
    }else if( ( is_threeofakind(h1) ) && ( is_threeofakind(h2) ) ){
	return threeofakind_check(h1, h2);
    }else if( ( is_twopairs(h1) ) && !( is_twopairs(h2) ) ){
	return 0;
    }else if( ( is_twopairs(h2) ) && !( is_twopairs(h1) ) ){
	return 1;
    }else if( ( is_twopairs(h1) ) && ( is_twopairs(h2) ) ){
	return twopairs_check (h1, h2);
    }else if( ( is_onepair(h1) ) && !( is_onepair(h2) ) ){
	return 0;
    }else if( ( is_onepair(h2) ) && !( is_onepair(h1) ) ){
	return 1;
    }else if( ( is_onepair(h1) ) && ( is_onepair(h2) ) ){
	return onepair_check(h1, h2);
    }else return compare_highcards(h1, h2);
}

int fourofakind_check ( hand_t h1, hand_t h2){
    int h1_val, h2_val;
    //using [2] insures it is part of the four of a kind
    h1_val = h1[2].value;
    h2_val = h2[2].value;

    if( h1_val > h2_val ){
	return 0;
    }else if ( h1_val < h2_val ){
	return 1;
    }

    int h1_high, h2_high;
    if( ( ( h1[0].value == h1[1].value ) && ( h1[1].value == h1[2].value ) && ( h1[2].value == h1[3].value ) ) ){
	h1_high = h1[4].value;
    }else{
	h1_high = h1[0].value;
    }
    if( ( ( h2[0].value == h2[1].value ) && ( h2[1].value == h2[2].value ) && ( h2[2].value == h2[3].value ) ) ){
	h2_high = h2[4].value;
    }else{
	h2_high = h2[0].value;
    }

    if( h1_high > h2_high ){
	return 0;
    }else if ( h1_high < h2_high ){
	return 1;
    }
    printf("ERROR IN FOUROFAKIND\n");
    exit(0);
}
int threeofakind_check ( hand_t h1, hand_t h2){
    int h1_val, h2_val, h1_higher, h2_higher, h1_high, h2_high;
    int i;
    for ( i = 0; i < 3; i++ ){
	if( ( h1[i].value == h1[i + 1].value ) && ( h1[i + 1].value == h1[i + 2].value ) ){
	    h1_val = h1[i].value;
	    if( i == 0){
		if( h1[3].value > h1[4].value ){
		    h1_higher = h1[3].value;
		    h1_high = h1[4].value;
		}else if( h1[3].value < h1[4].value ){
		    h1_higher = h1[4].value;
		    h1_high = h1[3].value;
		}
	    } else if( i == 1 ){
		if( h1[0].value > h1[4].value ){
		    h1_higher = h1[0].value;
		    h1_high = h1[4].value;
		}else if ( h1[0].value < h1[4].value ) {
		    h1_higher = h1[4].value;
		    h1_high = h1[0].value;
		}
	    }else{
		if( h1[0].value > h1[1].value ){
		    h1_higher = h1[0].value;
		    h1_high = h1[1].value;
		}else if( h1[0].value < h1[1].value ){
		    h1_higher = h1[1].value;
		    h1_high = h1[0].value;
		}
	    }
	    break;
	}
    }
    for ( i = 0; i < 3; i++ ){
	if( ( h2[i].value == h2[i + 1].value ) && ( h2[i + 1].value == h2[i + 2].value ) ){
	    h2_val = h2[i].value;
	    if( i == 0){
		if( h2[3].value > h2[4].value ){
		    h2_higher = h2[3].value;
		    h2_high = h2[4].value;
		}else if( h2[3].value < h2[4].value ){
		    h2_higher = h2[4].value;
		    h2_high = h2[3].value;
		}
	    }else if( i == 1 ){
		if( h2[0].value > h2[4].value ){
		    h2_higher = h2[0].value;
		    h2_high = h2[4].value;
		}else if( h2[0].value < h2[4].value ){
		    h2_higher = h2[4].value;
		    h2_high = h2[0].value;
		}
	    }else{
		if( h2[0].value > h2[1].value ){
		    h2_higher = h2[0].value;
		    h2_high = h2[1].value;
		}else if( h2[0].value < h2[1].value ){
		    h2_higher = h2[1].value;
		    h2_high = h2[0].value;
		}
	    }
	    break;
	}
    }
    if( h1_val > h2_val ){
	return 0;
    }else if( h1_val < h2_val ){
	return 1;
    }

    if( h1_higher > h2_higher ){
	return 0;
    }else if( h1_higher < h2_higher ){
	return 1;
    }else if( h1_high > h2_high ){
	return 0;
    }else if( h1_high < h2_high ){
	return 1;
    }
    printf("ERROR IN THREEOFAKIND\n");
    exit(0);
}

int twopairs_check ( hand_t h1, hand_t h2 ){
    int h1_high_val, h1_low_val, h2_high_val, h2_low_val, h1_high, h2_high;
    int i;

    if( ( h1[0].value == h1[1].value ) && ( h1[2].value == h1[3].value ) ){
	    h1_high_val = h1[2].value;
	    h1_low_val = h1[0].value;
	    h1_high = h1[4].value;
    }else if( ( h1[1].value == h1[2].value ) && ( h1[3].value == h1[4].value ) ){
	h1_high_val = h1[3].value;
	h1_low_val = h1[1].value;
	h1_high = h1[0].value;
    }else{
	h1_high_val = h1[3].value;
	h1_low_val = h1[0].value;
	h1_high = h1[2].value;
    }

if( ( h2[0].value == h2[1].value ) && ( h2[2].value == h2[3].value ) ){
	    h2_high_val = h2[2].value;
	    h2_low_val = h2[0].value;
	    h2_high = h2[4].value;
    }else if( ( h2[1].value == h2[2].value ) && ( h2[3].value == h2[4].value ) ){
	h2_high_val = h2[3].value;
	h2_low_val = h2[1].value;
	h2_high = h2[0].value;
    }else{
	h2_high_val = h2[3].value;
	h2_low_val = h2[0].value;
	h2_high = h2[2].value;
    }

    if( h1_high_val > h2_high_val ){
	return 0;
    }else if( h1_high_val < h2_high_val ){
	return 1;
    }else if( h1_low_val > h2_low_val ){
	return 0;
    }else if( h1_low_val < h2_low_val ){
	return 1;
    }

    if( h1_high > h2_high ){
	return 0;
    }else if( h1_high < h2_high ){
	return 1;
    }

    printf("ERROR IN TWOOFAKIND\n");
    exit(0);
}

int onepair_check ( hand_t h1, hand_t h2 ){
    sort_hand(h1);

    sort_hand(h2);
    int h1_val, h2_val;
    int i;
    int h1_swap, h2_swap;
    for ( i = 0; i < 4; i++ ){
	if ( h1[i].value == h1[i + 1].value ){
	    h1_val = h1[i].value;
	    h1_swap = i;
	    break;
	}
    }

    for ( i = 0; i < 4; i++ ){
	if ( h2[i].value == h2[i + 1].value ){
	    h2_val = h2[i].value;
	    h2_swap = i;
	    break;
	}
    }
    if( h1_val > h2_val ){
	return 0;
    }else if ( h1_val < h2_val ){
	return 1;
    }

    //A pretty bad way to make compare_highcards work if the pair is the same.
    h1[h1_swap].value = 0;
    h2[h2_swap].value = 0;
    h1[h1_swap + 1].value = 0;
    h2[h2_swap + 1].value = 0;

    sort_hand(h1);
    sort_hand(h2);
    compare_highcards(h1, h2);
}
/* compares the hands based solely on their highcard values (ignoring rank). if
 * the highcards are a draw, compare the next set of highcards, and so forth.
 */
int compare_highcards (hand_t h1, hand_t h2) {
    if( h1[4].value > h2[4].value ){
	return 0;
    }else if( h1[4].value < h2[4].value ){
	return 1;
    }else if( h1[3].value > h2[3].value ){
	return 0;
    }else if( h1[3].value < h2[3].value ){
	return 1;
    }else if( h1[2].value > h2[2].value ){
	return 0;
    }else if ( h1[2].value < h2[2].value ){
	return 1;
    }else if ( h1[1].value > h2[1].value ){
	return 0;
    }else if ( h1[1].value < h2[1].value ){
	return 1;
    }else if ( h1[0].value > h2[0].value ){
	return 0;
    }else if ( h1[0].value < h2[0].value ){
	return 1;
    }else printf("ERROR IN COMPARE_HIGHCARDS\n");
    exit(0);
}
