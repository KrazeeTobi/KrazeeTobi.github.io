/********************************************************************/
/*          readme.txt                                              */
/*          Communication Samples for AGB Multi-Cable               */
/*          2000/07/31                                              */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/

These samples and library are close to what would be the final specification, 
however, changes are still expected until it is finalized.

Samples
--------

multi_Boot
----------

 (Summary)
 This is a sample program that enables AGB without a Game Pak to play games by 
 booting and executing a program downloaded from an external source.

 (Connection)
 In order to operate this multi-boot sample (multi_boot.bin), connect the
 IS-AGB-EMULATOR only to the target board TS2 on master.  The target board of the
 slave needs to be connected only to the power and cable. 
 (It does not harm to connect other items.)

 It does not operate unless at least 2 units are connected.

 Connect power and cable according to "How to correctly connect AGB Multi-Cable 
 (for development)" (muliti_cable.txt).

 For details, see multi_boot.txt for reference. 


malti_sio
---------

 (Summary)
 This is a sample of multi-serial communication.  There is no difference 
 between the 2-player cable and the 4-player cable in AGB, and all the units are 
 connected by combining AGB multi-cables. This communication protocol is used when
 2 to 4 AGB are connected for communication.

 (multi_sio_response version)
 This is a version that emphasizes communication response.

 (multi_sio_safety version)
 This is a countermeasure version for communication error.

 (multi_sio_send_timer version)
 This is a version that conducts sending by timer interrupt.
 Rather than occupying one certain timer, communication interrupt became faster
 since the wait is omitted to adjust timing.

 (Connection)
 In order to operate multi-serial communication (multi_sio.bin), both the master 
 and slaves each require target board TS2 + IS - AGB-EMULATOR.  It does not operate
 unless at least two units are connected.

 Connect power and cable according to "How to correctly connect AGB multi-cable 
 for development" (muliti_cable.txt).

