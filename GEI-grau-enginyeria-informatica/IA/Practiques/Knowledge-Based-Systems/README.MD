# Knowledge Based System | IA-FIB-UPC
## Rico-rico menu generator

### What does it do?
Having a set of Ingredient, Dish and Drink instances it generates menus from those, having in mind some restrictions:

 * Preferred cuisine styles (Italian, Turkish, Chinese...)
 * Dietary restrictions (Kosher, Vegetarian, Gluten-free...)
 * Banned drink types (Alcohol, Caffeine...)
 * Available ingredients in that date.
 * Maximum money amount to spend.
 * Minimum money amount to spend.

#### Content
This practice contains the following:

 * rico_rico_rules.clp | Main clips file with rules.
 * rico_rico_functions.clp | Main clips file with functions and globals.
 * rico_rico.pont | Protégé generated ontology.
 * rico_rico.pins | Protégé generated instances.
 * rico_rico.pins.clp | Protégé generated instances with clips-readable format.
 * rico_rico.pprj | Protégé project.
 * run.clp | Automatizes program execution.
 * doc.tex | Documentation file in LaTeX.
 * instance_generator.py | To automatize instances generation from instance files.
 * Instance files for each class (Ingredient Drink MainCourse SecondCourse Dessert).

#### Run
To run the project you need to have CLIPS installed via CLI. Then just run the following command:

```bash
clips -f2 run.clp
```
If you are unable to install CLIPS via CLI, load each module manually in the same order as it's done in the 'run.clp' file.

#### Generate instances
To re-generate instances via Python script just follow next commands:

```bash
python instance_generator.py
```
