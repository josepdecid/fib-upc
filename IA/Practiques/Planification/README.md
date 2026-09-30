# Planification | IA-FIB-UPC
## Rico-rico weekly menu planificator

### What does it do?
Plans a weekly menu with first and second courses according to different restrictions such as:

 * Incompatibilities among first and second courses
 * Avoid repeating same dishes over a week
 * Avoid repeating categories in consecutive days
 * Fixed day-menu relations
 * Give caloric ranged menus
 * Give lower price menus

#### Content
This practice contains the following:

 * Linux folder | Source code to compile FF for Linux.
 * Windows folder | Source code to compile FF for Windows.
 * Linux_metrics folder | Source code to compile FF for Linux with metrics.
 * Templates folder | Folder with problem generator basic template and LaTeX documentation file.
 * Versions folder | From v0 to v5 with corresponding domain, problem files and tests.
 * executable.py | Executable that takes as parameters the version number and optional --e or --t to run example problems and test problems respectively.
 * generator.py | Generator that creates problems and takes as parameters the version number and number of tests to generate.

#### Run
To run the project you need to have CLIPS installed via CLI. Then just run the following command:

```bash
python3 executable.py [VERSION]
```
To run already created example problems:

```bash
python3 executable.py [VERSION] --e
```
To run generated test suites:

```bash
python3 executable.py [VERSION] --t
```
#### Generate problems
To generate random problems via Python script just follow next commands:

```bash
python3 generator.py [VERSION] [HOW_MANY]
```
