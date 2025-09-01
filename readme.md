# NameExporter

A C application for extracting and formatting student names from Moodle HTML export files. Built with GTK4, it provides both command-line and GUI interfaces to process HTML files containing student data and output formatted name lists.

---

## Description

NameExporter processes HTML files exported from Moodle that contain student names and submission status information. The program:

- Extracts student names from HTML markup
- Applies customizable formatting using prefix/suffix files
- Sorts and processes names with configurable markers
- Outputs formatted results to a text file
- Supports both command-line and GUI operation
- Handles up to 999 student names per file

---

## Requirements

- **GTK4**: https://www.gtk.org/docs/installations/
- C compiler (GCC recommended)
- Make utility (for compilation)

---

## Installation

### Option 1: Compile from Source

1. Install GTK4 following the official guide: https://www.gtk.org/docs/installations/
2. Clone or download this repository
3. Compile using the provided Makefile:
   ```bash
   make
   ```

### Option 2: Pre-compiled Windows Version

1. Download the pre-compiled package: https://www.tud.ttu.ee/web/jofing/kju.zip
2. Extract the ZIP file to your desired directory
3. Use the `.bat` file in the main folder to run (equivalent to running the `.exe` directly)

---

## Configuration Files

- **`input.txt`**: Moodle HTML export containing student data
- **`marker.txt`**: Defines markers for name processing
- **`prefix.txt`**: Sets prefix formatting for output names
- **`suffixa.txt`**: Configuration for suffix type A
- **`suffixd.txt`**: Configuration for suffix type D

---

## Required Files

The following files must be present in the same directory as the program:

```
NameExporter/
├── nameexporter           # compiled executable (Linux)
├── nameexporter.exe       # compiled executable (Windows)
├── input.txt              # Moodle HTML export file
├── marker.txt             # marker configuration
├── prefix.txt             # name prefix formatting
├── suffixa.txt            # suffix configuration A
├── suffixd.txt            # suffix configuration D
└── output.txt             # generated output (created by program)
```

---

## Usage

### Command Line Mode

Run the program with the input filename as an argument:

```bash
./nameexporter input.txt
```

The program will process the file and generate `output.txt` with formatted names.

### GUI Mode

Run the program without arguments to launch the graphical interface:

```bash
./nameexporter
```

**GUI Features:**
- **File Status Panel**: Left side shows all required files with status indicators
- **Error Indicators**: Red boxes indicate file problems with specific error messages
- **Automatic Rename**: If `output.txt` exists, click "RENAME" to backup with timestamp
- **Process Button**: Click "RUN" when all files are ready to generate output

---

## Error Handling

**Common Issues:**

- **Name Limit**: Program stops processing after 999 names (maximum capacity)
- **Missing input.txt**: Program will terminate or produce empty output
- **Invalid HTML Content**: May cause unexpected results or program termination
- **Corrupted Config Files**: Incorrect `marker.txt`, `prefix.txt`, `suffixa.txt`, or `suffixd.txt` content will produce malformed output

**Troubleshooting:**
- Verify all required files are present and readable
- Check that `input.txt` contains valid Moodle HTML export data
- Ensure configuration files contain proper formatting rules
- Use GUI mode to identify specific file issues before processing

---

## Tested Systems

- **Linux** (fully tested)
- **Windows 11** (pre-compiled version available)
- GTK4 installed and accessible

---