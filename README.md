# FlashCards
C++ Windows desktop application for digital flash cards

## Features:
- When answering a flash card, temporal handwritten or text annotations can be made
- Filter card sets and card with text search
- Drag and drop of flash cards and card sets to change the display order
- Study through the cards in order, randomized or depending on the score (study until each card has 100%)
- Synchronisation of cards between devices e.g. via OneDrive or Google Drive

## Design
- Folder structure with flash cards and card sets, scrollable
- Direct manipulation
- Right click pop-up menu to manipulate flash cards and card sets
- Selection of multiple items with a selection rect when holding the left mouse button (or Ctr + A)

#### Flash card:
- Front and back with text, handwritten annotations and files (screenshots, images, pdfs, audio)
- Has a score from 0% to 100% that shows the learning curve (e.g. when the card was min. answered 3 times correctly -> 100%)
- Can be created, edited, deleted and moved (copied/cut) into another card set
- Shown as a single flash card with its front side and the score

#### Card set:
- Contains n flash cards, new cards can be added, containing cards can be deleted
- Colored, has a title and a display order (e.g. priority)
- Scores on cards can be cleared/reset to 0%
- Can be created, edited, deleted and moved
- Shown as a stack of the containing flash cards (the more cards, the higher the stack)

#### Card set browser
- Browse through all card sets, scoll down with mouse wheel
- Select a set with one left mouse button click, open a set with a left mouse button double click
- Select multiple sets with a left mouse click drag (selection rect)
- Right mouse click with pop-up menu (add new card, edit this card set, delete this card set, study this card set)
- Drag and drop of selected card sets to change the display order

#### Flash Card viewer
- Change between front and back with a left mouse button double click
- Switch on/off handwritten annotations with a singe right mouse button click (show indicator)
- Show different tools in annotation mode (undo/redo, eraser, colors, ...)
- On the back side the score can be increased if the answer was correct
