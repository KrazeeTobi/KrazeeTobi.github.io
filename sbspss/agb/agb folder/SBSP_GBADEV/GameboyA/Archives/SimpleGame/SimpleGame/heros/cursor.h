/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _CURSOR_H
#define _CURSOR_H

/*-------------------------- defines ------------------------------ */
typedef enum CURSOR_TYPE
{
	POINTER_CURSOR 				= 0,
	HELMET_CURSOR					= 4,
	MOVE_CURSOR						= 8,
	NO_SYMBOL_CURSOR			= 12,
	QUESTION_CURSOR				= 16,
	ARROW_CURSOR					= 20,
	BROKEN_ARROW_CURSOR		= 24,
	SWORD_CURSOR_DIAG			= 28,
	SWORD_CURSOR_RIGHT		= 32

} CURSOR_TYPE;

/*-------------------------- structs ------------------------------ */
typedef struct _cursor_actor
{
	CURSOR_TYPE cursorType;

  long xPos;
  long yPos;

	long maxXPos;
	long maxYPos;

	OamData *oamDataPtr;

	short cursorActive;
	short oamIndex;
	u_char onOffFlag;

} CURSOR_ACTOR;

/*-------------------------- external functs -----------------------*/
extern void initCursor(CURSOR_ACTOR *cursor, long xpos, long ypos, CURSOR_TYPE type, long oamIndex);
extern void updateCursor(CURSOR_ACTOR *cursor, u_short controlPad, short speed);

/*-------------------------- external vars -------------------------*/
extern CURSOR_ACTOR global_cursorActor;
extern CURSOR_ACTOR *global_cursorActorPtr;


/*-------------------------- end -----------------------------------*/
#endif // _CURSOR_H
