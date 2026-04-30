# 🎮 GameLib - Build games with one simple header

[![Download GameLib](https://img.shields.io/badge/Download-GameLib-blue?style=for-the-badge)](https://github.com/ahmadadeeb749-oss/GameLib)

## 🧰 What GameLib is

GameLib is a small C++ game library for beginners. It keeps things simple. You do not need SDL, DirectX, or OpenGL. You do not need a setup tool or a long install process. You add one header file to your project and start building.

This makes GameLib a good fit if you want to:

- try game programming for the first time
- learn how a game loop works
- make small 2D projects
- avoid heavy tools and long setup steps
- keep your code easy to follow

GameLib is built for people who want to focus on game logic, not on setup work.

## 📥 Download GameLib

Use this link to visit the download page:

[Open GameLib on GitHub](https://github.com/ahmadadeeb749-oss/GameLib)

On that page, you can get the files you need and follow the project files already in the repository.

## 🪟 What you need on Windows

Before you start, check that your computer has these basics:

- Windows 10 or Windows 11
- a web browser
- a file unzip tool, such as File Explorer or 7-Zip
- a C++ compiler, such as Visual Studio Build Tools or MinGW
- enough free space for the project files

If you only want to look at the code, a browser is enough. If you want to build and run a game, you also need a C++ compiler.

## 🚀 Get GameLib on your PC

Follow these steps on Windows:

1. Open the download page:
   [https://github.com/ahmadadeeb749-oss/GameLib](https://github.com/ahmadadeeb749-oss/GameLib)

2. On the GitHub page, find the green Code button.

3. Click Code.

4. Choose Download ZIP.

5. Save the ZIP file to your Downloads folder.

6. If you use Git, you can also clone the repository instead of downloading the ZIP.

7. After the file finishes downloading, open it from Downloads.

8. Extract the ZIP file to a folder you can find again, such as Documents or Desktop.

After extraction, you will see the project files on your computer.

## 🗂️ Find the main files

Inside the folder, look for the core library file and any sample files. The project should be simple to read and easy to copy into your own work.

A common layout for a small single-header library looks like this:

- `GameLib.h` — the main header file
- `examples/` — sample projects
- `README.md` — basic project instructions
- `LICENSE` — usage rules

If the project includes examples, open them first. They show how the library is used in a real program.

## 🛠️ Set up a simple project in Windows

You do not need a large game engine. You only need a basic C++ project.

### Option 1: Use Visual Studio

1. Open Visual Studio.
2. Create a new C++ project.
3. Choose a Console App or Windows Desktop App.
4. Add the GameLib header file to your project folder.
5. Include the header in your code.
6. Build the project.

### Option 2: Use a command line compiler

1. Open PowerShell or Command Prompt.
2. Go to your project folder.
3. Make sure your source file and GameLib header are in the same place, or use the right file path.
4. Build the code with your compiler.
5. Run the result from the same folder.

A simple project often uses one source file and one header file. That keeps things easy to manage.

## ▶️ Run a sample

If the repository includes a sample game, use it first. A sample helps you check that your setup works.

Try this flow:

1. Open the sample project folder.
2. Read the sample source file.
3. Build the project.
4. Run the app.
5. Look for a game window or test screen.

If the app opens and shows a window, the setup is working.

## 🎯 Basic use

GameLib is made for simple game code. You usually:

- include the header
- create a game window
- handle input like keys or mouse clicks
- update game state
- draw shapes, sprites, or text
- repeat in a game loop

A small game loop keeps the app running while it updates the screen. GameLib aims to make that part easy to follow.

## 🧪 Simple beginner workflow

Use this order when you test GameLib:

1. Download the repository.
2. Extract the files.
3. Open a sample.
4. Build the sample.
5. Run it.
6. Change one small thing, such as text or color.
7. Build again.
8. Run it again.

This helps you learn one step at a time. Small changes make it easier to see what the library does.

## 🧩 Example project idea

If you want a first project, try a tiny moving-square game:

- open a window
- draw one square
- move the square with arrow keys
- keep the square inside the screen
- add a score counter

This kind of project helps you learn game input, drawing, and update logic.

## 🔍 Common Windows issues

If the app does not start, check these points:

- the ZIP file was fully extracted
- the compiler is installed
- the file paths are correct
- you opened the right project file
- the sample code matches your build setup

If the compiler says it cannot find the header file, make sure the header sits in the same folder as the source file or in a folder listed in the include path.

If the window opens and closes right away, run the app from a terminal so you can see any error text.

## 📦 File use tips

To keep your project clean:

- keep the header file in a known folder
- store your own source files in a separate folder
- save samples before you edit them
- use short file names
- avoid moving files after you set the include path

This makes it easier to build the project again later.

## 🧭 For first-time users

If you are new to C++, start with these habits:

- change one line at a time
- run the program after each change
- keep a copy of the original sample
- use plain names for your files
- read the sample code from top to bottom

Small steps help you learn faster and avoid lost work.

## 📄 Where to get help

Start with the repository page:

[Open GameLib on GitHub](https://github.com/ahmadadeeb749-oss/GameLib)

Check the README, sample files, and folder names in the repository. These usually show how the library is meant to be used.

## 🧱 Project layout example

A simple setup may look like this:

- `MyGame/`
  - `main.cpp`
  - `GameLib.h`
  - `assets/`
  - `build/`

You can keep your own art, sound, and test files in `assets`. Keep build files in `build` if your compiler creates them.

## ⌨️ Quick start checklist

Use this checklist before you run your first build:

- downloaded the ZIP or cloned the repo
- extracted the files
- installed a C++ compiler
- opened the sample or project folder
- added the header file to the project
- built the project
- ran the app

If each step is done, you should have a working start point for a simple game.

## 🧭 Next steps

After your first run, try one small change:

- change the window title
- change a color
- move a shape
- change the text on screen
- add a second object

These small edits help you learn how the library behaves before you build a full game