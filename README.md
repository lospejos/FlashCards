# FlashCards
C++ Windows desktop application for digital flash cards

## Features:
- When answering a flash card, temporal handwritten or text annotations can be made
- Filter card sets and card with text search
- Drag and drop of flash cards and card sets to change/sort the display order
- Study through the cards in order, randomized or depending on the score (study until each card has 100%)
- Synchronisation of cards between devices e.g. via OneDrive or Google Drive (probably just via folder synchronization)

## Design
- Folder structure with flash cards and card sets, scrollable
- Direct manipulation
- Right click pop-up menu to manipulate flash cards and card sets
- Selection of multiple items with a selection rect when holding the left mouse button (or Ctr + A)
- Main configuration file inside the main folder in which all card sets are stored

### Flash card:
- Front and back with each max. one text, one handwriting, one images and one screenshot
- Has a score from 0% to 100% that shows the learning curve (e.g. when the card was min. answered 3 times correctly -> 100%)
- Has a display order inside card set (-> cards can be sorted)
- Can be created, edited, sorted, deleted and moved (copied/cut) into another card set
- Shown as a single flash card with its front side and the score
- Save as all in one XML file in the corresponding card set folder

### Card set:
- Contains 0 - n flash cards, new cards can be added, containing cards can be deleted
- Colored, has a title and a display order (e.g. priority)
- Scores on cards can be cleared/reset to 0%
- Can be created, edited, deleted and moved
- Shown as a stack of the containing flash cards (the more cards, the higher the stack)
- Save as a folder with the name of the card set and maybe a configuration file

#### Site - card set browser
- Browse through all card sets, scoll down with mouse wheel
- Select a set with one left mouse button click, open a set with a left mouse button double click
- Add a new set with a left mouse button double click on the corresponding icon (displayed as empty card set with a + symbol under all card sets)
- Select multiple sets with ctr+left mouse button click or a left mouse click drag (selection rect)
- Right mouse click with pop-up menu for no selection (-> add new card set), single card set selection (-> study, -> add new flash card, -> edit, -> delete) and multiple card set selection (-> delete)
- Drag and drop of selected card sets to change/sort the display order

#### Site - card set viewer
- Browse through all flash cards inside a specific card set
- Selection scheme and drag and drop the same as for card sets
- Right mouse click with pop-up menu for no selection (-> add new flash card), single flash card selection (-> clear score, -> edit, -> delete) and multiple flash card selection (-> study, -> clear scores, -> delete)
- Buttons to study the card set (study in display order, study in random order, study by scores) 

#### Site - flash card viewer
- Switch between front and back with a left mouse button double click
- Switch on/off annotation mode with a right mouse button click
- Annotation mode: yellow flash card, draw on it with left mouse button click, button to switch between erazer and pen, buttons for stroke width
- On the back side the score can be increased if the answer was correct (by clicking once on a tick icon inside the score circle, gives immediate feedback)
- Maybe provide side-by-side (or top-down) comparison between the annotation and the back of the card

#### Site - flash card editor
- Switch between front and back with a button
- Buttons for adding text, handwriting, image and screenshot
- Selection indicator (rect with dashed lines, corners for scaling, center for move)
- Every item is a represented as a rect, no item can be on top of another
- Select an item with one left mouse button click on the item
- Pop-up menu with one right mouse button click for text (-> edit text, -> delete), handwriting (-> edit handwriting, -> delete), image (-> change image, -> delete) and screenshot (-> take new screenshot, -> delete)
- Scale and move every item with a left mouse button drag on the selection indicator

#### Editing - text
- Show text position with blinking vertical indicator
- Alignment is from left to right, the text is at all times inside the rect and fills it out nicely
- Character size = min(rect_height/count_lines, size_to_fit_longest_line_into_rect)
- Size of the rect controls the size of the characters (higher rect -> larger characters)
- If a text line reaches the right end and the user continues to type the characters will shrink
- A new line will (if possible) increase the rect size without influencing the character size
- Allow tabulater as text input and positioning in the text via arrow keys

#### Editing - handwriting
- Site with the same layout and functionality as the annotation
- White background
- Cancel and OK button

#### Editing - image
- Open Dialog Box to select the image

#### Editing - screenshot
- New Site filled out with the screenshot
- Select the wanted piece with a selection rect (left mouse button drag)
- Cancel and OK button