# List Folders (Qt version)

[![Download List Folders](https://sourceforge.net/sflogo.php?type=11&group_id=2452708)](https://sourceforge.net/projects/listfolders/files/Qt)

Main features:

- List files and subfolders of a selected directory.
- Filter files by extension (include/exclude).
- Filter root directories by name (include).
- Export to text, tree.
- Select export name.
- View tree structure of exported directory using internal Tree Viewer.

## Description

The program is used to list files and subfolders inside a selected local file system path. 
It is possible to customize filters to exclude/include files and include directories. 
These export options are available:

 - **Export Text** - get text file with the folder structure
 - **Export Tree** - get JSON and HTML files for [jsTree](http://jstree.com/) jQuery plugin to view folder structure in tree mode
 
Additional **Export name** field allows set different name for exported files. By default the root folder name is used.


## Requirements

1. To build from source - [Qt5.3.1](http://download.qt.io/official_releases/qt/5.3/5.3.1/).


## Install & Run

1. Run the **List Folders.exe** or **List Folders.msi** installer and pass all steps ([installer on SourceForge](https://sourceforge.net/projects/listfolders/files/Qt/)).
2. The **Desktop** and **Start Menu** *shortcuts* should be created.
3. Start the program with the shortcut or using the **List Folders.exe** file from the installed directory.


## Usage

1. Paste a directory path in the **Path** field.
2. Add extensions to **Filter Extensions** to include only files with specified extensions.
3. Add extensions to **Exclude Extensions** to exclude files with these extensions (the **Filter Extensions** text will be ignored).
4. Add folder names (that are subfolders or current directory from the path) to **Filter Directories** to include only these directories.
5. Select **Export Options**

      - **Export Text** - creates `.txt` file with the directory structure in the `export/text` folder.
      - **Export Tree** - creates two files: `.html` in the `export/tree` subfolder of the project main folder and `.json` in the `export/tree/json` subfolder.
      The `.html` file can be run directly to view the scanned directory content in the tree format. It uses jsTree plugin for jQuery to give representation and interaction of a file tree on the HTML page.  

6. Using the field **Export Name** you may set your name which will be given to `.html` and `.json` files in the `export/tree` folder when the tree view is exported. Or leave it blank to use the selected directory as the Tree name.
7. Press **Scan Directory**.
8. During the scanning the statistic information should appear in the bottom textarea. 
9. After the scan the `export` subfolders should contain exported files with scanned structure.
10. To check tree view go to `export/tree` and open `.html` file in browser. It should show the directory structure with expandable tree branches.


## Tree Viewer

1. Press **Tree Viewer** button.
2. Paste the path to the JSON file with tree structure to the **Path** field or use **Browse** button to select the file. The default browse location should point to the `export/tree/json` folder with exported JSON files.
3. Press **Load Tree** to show the file structure in the main area.


## Shortcuts

- **Ctrl+O** - Browse for directory in the **Main window** / browse for JSON file in the **Tree Viewer**
- **Ctrl+R** - Scan directory
- **Esc** - Exit **Main window** / **Tree Viewer**


## Screenshots

![list-folders-main](/files/list-folders-main.png)
![tree-viewer](/files/tree-viewer.png)


## Comparison with C# and Java versions

- Requires less memory
- Faster scanning
- Uses local database (**SQLite**), no need to install **MySQL** server
- Uses local **Qt libraries**, no need to install additional packages
