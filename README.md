# Castle-Covert-Channel

PLEASE NOTE:  0 A.D. is an open-source game which is still under development. One of the things in their TODO is to implement end-to-end encryption. So until that is done, Castle over 0 A.D. is NOT secure as described in the paper.

However, Castle is secure as described in the paper when it is put to work on top of any other RTS game which does have encryption implemented. Anyone wanting to do this should be able to in a few hours given the code that we released. If 0 A.D. were to implement end-to-end encryption, Castle over 0 A.D. would be secure as claimed in the paper.

Read the full paper here: http://arxiv.org/abs/1503.05904

For any Castle related help, you can send an email to castle@googlegroups.com


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
	

----------------------------------------------------------------
Extending Castle to work over other RTS-games
----------------------------------------------------------------

If you wish to use Castle with RTS games which are not 0 A.D., you will have to put in a few hours of work.

First, you must select your RTS of choice. This game must have a map editor, a replay feature, and there must 
be a crack of some sort for the replay files, online.

Once you have selected your RTS game, you can make the map. You are immediately faced with two options when 
making the map; immobilized units or buildings. You want to select whichever takes up less screen space.  
This means finding the smallest building that can create a rally point in your given game and comparing it to 
the smallest way to immobilize any unit in your game. Once you have selected units or buildings, you place a 
grid of them for each player, filling as much of the screen as can be used. Keep in mind that some parts of 
the game UI may expand to cover parts of the screen and thus, you cannot use those parts of the screen for 
units/buildings. Once you have your grids layed out, you can save the map.

Next, familiarize yourself with the replay format of the game that you have selected. The units/buildings 
should have ascending IDs from when you placed them. They may not go up by 1 every time but they should go 
up linearly. Write down the lowest and highest ID for each player, you will use this for decoding. If you 
elected to place your grid boustrophedonically, your ID system will be wonky and you will have a bit of a 
headache for encode/decode. I suggest having your grid be ordered by rank and file (this allows for simple 
modular arithmetic to determine the location of an index in the grid).

Once your map is set up and you are familiar with your replay system, you can modify the SendMove.ahk script.  
Please try to familiarize yourself with AutoHotkey before attempting to change AHK scripts; AHK has some very 
interesting syntax.

Getting deeper into Castle, you can get into changing fundamental encode/decode within Castle. In theory, all 
that you should need to change in encoder.py, is num_buildings and the maximum number of units that can be 
selected in an encoding. Note, we randomly decide, for a given encoding of a few bytes, how many units will 
be sent. This more evenly distributes our packet sizes and looks more like an ordinary game. What is important 
to you is that we use a maximum unit selection of 200 (the max for 0AD) and that you can use whatever number 
you would like. The 0adProcessor code for Castle is mostly file I/O and CLI but there are some things that you 
will want to familiarize yourself with: how moves are being sent and received in AHKHandler and FileManager. 
Particularly in AHKHandler::SendMove, there are a lot of edge case handling checks that may seem unintuitive. 
Feel free to email if you have any questions.

Finally, you can remove or modify the menuing scripts and CLI from Castle, which are 0 A.D. specific.

When modifying Castle to work with different RTS games, take note of what gets recorded in your game's replay 
file and what doesn't. Some games store every unit selection, which drastically speeds up moves.You no longer 
need to select some subset of units and give a command; you can simply select units in turn, never giving any 
commands. Also take note of the unique features of your given RTS that can be used to your advantage. If you 
are really interested in this project and have the time to devote, there are generally Trigger Systems 
integrated in most RTS games and these limit your capabilities only by your imagination.


