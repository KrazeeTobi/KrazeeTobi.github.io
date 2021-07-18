/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "main.h"
#include "cursor.h"


// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================
CURSOR_ACTOR global_cursorActor;
CURSOR_ACTOR *global_cursorActorPtr;

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================


/*
 *	void initCursor(CURSOR_ACTOR *cursor, long xpos, long ypos, CURSOR_TYPE type, long oamIndex)
 *
 *  PARAMETERS:		cursor:		Pointer to cursor actor
 *                xpos:			Initial X pos of cursor
 *                ypos:			Initial Y pos of cursor
 *                type:			Cursor type
 *                oamIndex:	Oam index for cursor
 *
 *  DESCRIPTION:	Inits the cursor
 *
 *  RETURNS:			Nothing
 */
void initCursor(CURSOR_ACTOR *cursor, long xpos, long ypos, CURSOR_TYPE type, long oamIndex)
{
	global_cursorActorPtr = cursor;

	cursor->onOffFlag		= ON;
	cursor->xPos 				= xpos;
	cursor->yPos 				= ypos;
	cursor->cursorType 	= type;
	cursor->oamIndex 		= oamIndex;
	cursor->oamDataPtr 	= &global_oamData[oamIndex];
}

/*
 *	void updateCursor(CURSOR_ACTOR *cursor, u_short controlPad, short speed)
 *
 *  PARAMETERS:		cursor:			Pointer to cursor actor
 *                controlPad:	Current value of control pad
 *                speed:			Cursor speed
 *
 *  DESCRIPTION:	Updates cursor pos
 *
 *  RETURNS:			Nothing
 */
void updateCursor(CURSOR_ACTOR *cursor, u_short controlPad, short speed)
{
	if (controlPad & U_KEY) {
		cursor->yPos -= speed;
	}

	else if (controlPad & D_KEY) {
		cursor->yPos += speed;
	}

	if (controlPad & L_KEY) {
		cursor->xPos -= speed;
	}

	else if (controlPad & R_KEY) {
		cursor->xPos += speed;
	}
}

