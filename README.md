===========================
===========================
Author: Michael Kern
Date: 18.09.2013

Samsung TV - ChannelManager
===========================
===========================

Description
===========

Channel manager for Samsung TVs to manually manage and organize channels via GUI (C++ / Windows)

Major Objectives
================

- GUI, providing clear overview of channel list and their data (number, frequency, encryption,....)
	+ Qt 5.1.1 / Qt 4.8.3
	+ List view (left) and channel detail view (right)
	+ Channel moving: Drag/Drop, keyboard shortcut (+/-) or via item in channel context menu 
	+ Support multiple view -> favorites, digital, analog, ...
	
- Read and write back SAMSUNG scm files
	+ Minizip (from zlib 1.2.5)
	+ Read scm files and obtains their raw data
	+ Modify data of files
	+ Save files back to scm
	
Changelog
=========
Version 0.0.1
18.09.2013
- [new] implemented reading and writing of scm files
- [new] support obtaining and modifying/updating data content of specific files within the scm file
