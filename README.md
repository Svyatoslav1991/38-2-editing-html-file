Creating an Application to Edit an HTML File

What should be done
Create an application that splits a window into two halves.
In the left half you can edit the HTML document, and in the right half you can see the result of the WebView.

You can use Qt Creator and Qt Designer to quickly add two elements:
QPlainTextEdit for editing text,
QWebEngineView to display the result.

It is necessary that each of the widgets takes up an equal amount of space horizontally and all of it vertically.

What is being assessed
The application displays one window in which there are two text widgets.
Each widget takes up its own half of the screen.
The left widget contains a text representation of the HTML document, the right one contains a drawn web page.
When you change the page source code in the left widget, the view in the right one immediately changes.
