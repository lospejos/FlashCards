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
- Selection of multiple items with a selection rect when holding the left mouse button

#### Flash card:
- Front and back with text, handwritten annotations and files (screenshots, images, pdfs, audio)
- Has a score from 0% to 100% that shows the learning curve (e.g. when the card was min. answered 3 times correctly -> 100%)
- Can be created, edited, deleted and moved (copied/cut) into another card set
- Shown as a single flash card with its front side and the score

#### Card set:
- Contains n flash cards, new cards can be added, containing cards can be deleted
- Colored and has a title
- Scores on cards can be cleared/reset to 0%
- Can be created, edited, deleted and moved
- Shown as a stack of the containing flash cards (the more cards, the higher the stack)
