# About this project
This is C++ multiplayer Tetris project including single-mode and multi-mode

Now only a single mode is implemented

This project provides a library for text-based UI and Tetris code.

# How to use
```
1. download these codes
2. just execute a project(tetris_client/tetris_client.sln)
```
# Library
* Text-based Painter
  * You can draw lines and simple figures at a desired position on the screen.
  * You can change color and basic text corresponding to a point of the figure.

* Text-based Printer
  * You can draw a text box at a desired position on the screen.
  * You can align a text (Top, Center, Botto,), (Left, Center, Right)

* Text Console UI
  * This is based on a Text-based Panter and Printer.
  * This allows you to construct simple UI  
  * You can select the desired element with the arrow keys.
  * You can interact with it using a key (we use the space bar).
  * Pop Up Event is implemented.
  
* File accessor
  * You can access local files.
  * You can manage member information and score information so on.
    
* Tetris
  * Client: Single-Mode & Multi-Mode(not yet)
  * Server: (not yet)
  
# Scene
<table>
  <tr>
   <td>Single Mode</td>
  <tr>
  <tr>
    <td><img src="https://github.com/hoonisone/multi_tetris/assets/56896592/0ee814d0-ee34-4f28-940b-cff15acb6c9b"></td>
  <tr>
  <tr>
   <td>Score</td>
  <tr>
  <tr>
    <td><img src="https://github.com/hoonisone/multi_tetris/assets/56896592/d9e26926-3c06-4b53-887d-192fd1e8c378"></td>
  <tr>
     <tr>
   <td>Server Connection</td>
  <tr>
  <tr>
    <td><img src="https://github.com/hoonisone/multi_tetris/assets/56896592/a14a5d84-9214-4ca1-a177-cf5d72a12c89"></td>
  <tr>
</table>
