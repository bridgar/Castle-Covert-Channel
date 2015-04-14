# Castle-Covert-Channel

PLEASE NOTE:  0 A.D. is an open-source game which is still under development. One of the things in their TODO is to implement end-to-end encryption. So until that is done, Castle over 0 A.D. is NOT secure as described in the paper.

However, Castle is secure as described in the paper when it is put to work on top of any other RTS game which does have encryption implemented. Anyone wanting to do this should be able to in a few hours given the code that we released. If 0 A.D. were to implement end-to-end encryption, Castle over 0 A.D. would be secure as claimed in the paper.


CASTLE COVERT CHANNEL INSTALLATION GUIDE
-----------------------------------------------------------------

!!WARNING!!
This release of Castle currently only works with monitors of at least horizontal resolution 1600.


1. Install 0ad, found at http://play0ad.com/download/

2. Install at least Python 2.7 and make sure that you have it in your PATH

3. Install AutoHotkey, found at http://www.autohotkey.com/

4. Place the entire 0adProcessor folder into your C directory. Now, you should have C://0adProcessor

5. Copy local.cfg from C://0adProcessor/Config into %appdata%/../local/0 A.D. alpha/binaries/data/config

6. Copy Blank_Map.xml and Blank_Map.pmp from C://0adProcessor/Map into %appdata%/../local/0 A.D. alpha/binaries/data/mods/public/public.zip/maps/scenarios


----------------------------------------------------------------
THINGS OF NOTE
----------------------------------------------------------------
The correctness of Castle transmissions is heavily dependant upon the performance of 0ad. Castle pushes 0ad to its limits. Performance of 0ad will vary from machine to machine. Do not assume that a high-end processor alone will make 0ad performant; on-board graphics cards probably won't cut it for this. If you see 0ad visibly straining to keep up with the commands being input (selection boxes trailing behind the clicking cursor or game screen freezing momentarily), you can do several things to increase performance:
	-First, go into C://0adProcessor/Scripts/SendMove.ahk. On line 35, delete the leading semicolon. Be sure to recompile SendMove.ahk or the changes will not be made. Do this by right clicking SendMove.ahk and clicking compile script. This will uncomment the sleep before every click that the script will execute. It should be noted that out-of-the-box AutoHotkey cannot maintain sleep accuracy below ~20ms (meaning all sleeps below 20ms will last 20ms) but several methods for achieving precise sleep with AutoHotkey exist online.
	-Second, if your 0ad is still not performant enough, you can attempt to change the map to have fewer buildings in the game. The map with the release version of Castle has 800 buildings per player. The python script used to generate the map file is contained in C://0adProcessor/Map. If you do elect to change the number of buildings in the map, you will have to change some code. In C://0adProcessor/Encoder/encoder.py, change num_buildings on line 142. In the castle source, change num_buildings in stdafx.h
	

Read the full paper here: http://arxiv.org/abs/1503.05904

For any Castle related help, you can send an email to castle@googlegroups.com


