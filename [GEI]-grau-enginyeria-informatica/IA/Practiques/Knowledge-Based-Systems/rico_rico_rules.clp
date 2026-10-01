; Thu May 11 16:35:07 CEST 2017
;
;+ (version "3.5")
;+ (build "Build 663")

;%%%%%
;%
;% DETERMINE USER RULES
;%
;%%%%%

(defrule print-welcome-message "Initial program message"
  (declare (salience 0))
  =>
  (printout t "*-------------------------------------------------------------------------------------" crlf)
  (printout t "|                                                               ___          /|      |" crlf)
  (printout t "|     * Eric Dacal                                 ||||     .-''   ''-.     } |  __  |" crlf)
  (printout t "|     * Josep de Cid                          |||| ||||   .'  .-'`'-.  '.   } | /  \\ |" crlf)
  (printout t "|     * Joaquim Marset                        |||| \\  /  /  .'       '.  \\  } | |()| |" crlf)
  (printout t "|                                             \\  /  ||  /  :           :  \\  \\| \\  / |" crlf)
  (printout t "|                Welcome to                    ||   ||  | :             : |  ||  ||  |" crlf)
  (printout t "|     _____                _____               %%   %%  | :             : |  %%  %%  |" crlf)
  (printout t "|   (, /   ) ,           (, /   ) ,            %%   %%  \\  :           :  /  %%  %%  |" crlf)
  (printout t "|     /__ /    _  _        /__ /    _  _       %%   %%   \\  '.       .'  /   %%  %%  |" crlf)
  (printout t "|  ) /   \\__(_(__(_)    ) /   \\__(_(__(_)      %%   %%    '.  `-.,.-'  .'    %%  %%  |" crlf)
  (printout t "| (_/                  (_/                     %%   %%      '-.,___,.-'      %%  %%  |" crlf)
  (printout t "*-------------------------------------------------------------------------------------" crlf "|" crlf)
)

(defrule determine-event-type "Asks for event type"
	(declare (salience -1))
	(not (event event-type ?))
	=>
	(bind ?type (ask-question-opt "Which type of event will it be? " ?*EVENT_TYPES*))
  (if (eq ?type Familiar) then
    (assert (event familiar TRUE))
  )
)

(defrule determine-event-date "Asks for dates"
  (declare (salience -2))
  (not (and (event month ?) (event hour ?)))
  =>
  (bind $?answer (ask-question-date-format "Tell me the event date [DD MM]"))
	(bind ?day (nth$ 2 ?answer))
	(bind ?month (nth$ 3 ?answer))
  (assert (event day ?day))
  (assert (event month ?month))
)

(defrule determine-event-guests "Asks for number of assistants"
  (declare (salience -3))
  (not (event guests ?))
  =>
  (bind ?guests (ask-question-num "How many guests will there be? " 1 10000))
  (assert (event guests ?guests))
)

(defrule determine-preferred-cuisine-styles "Asks for preferred cuisine styles"
  (declare (salience -4))
  (not (event preferred-cuisine-styles $?))
  =>
  (bind $?styles (ask-question-multi-opt "Which cuisine styles do you prefer? " ?*CUISINE_STYLES*))
  (assert (event preferred-cuisine-styles $?styles))
)

(defrule determine-dietary-restrictions "Asks for dietary restrictions"
  (declare (salience -5))
  (not (event dietary-restrictions $?))
  =>
  (bind $?restrictions (ask-question-multi-opt "Any dietary restrictions? " ?*DIETARY_RESTRICTIONS*))
	(assert (event dietary-restrictions ?restrictions))
)

(defrule determine-drinks "Asks for banned drinks and if one drink per dish is required"
	(declare (salience -6))
	(not (and (event drink-per-dish ?) (event drink-types ?)))
	=>
	(bind ?drink-per-dish (ask-question-yes-no "Will you require a drink for each dish? "))
	(bind ?drink-types (ask-question-multi-opt "Would you discard any drinks? " ?*DRINK_TYPES*))
	(if ?drink-per-dish then
		(assert (event drink-per-dish TRUE))
	)
	(assert (event drink-types ?drink-types))
)

(defrule determine-price-range "Asks for event menu price range"
	(declare (salience -7))
	(not (and (event price-min ?) (event price-max ?)))
  =>
  (while TRUE do
		(bind ?price-min (ask-question-num "Minimum price to pay? " 0 10000))
    (bind ?price-max (ask-question-num "Maximum price to pay? " 0 10000))
    (if (>= ?price-max ?price-min) then (break))
    (printout t "| Maximum price must be greater than minimum price" crlf)
  )
  (assert (event price-min ?price-min))
  (assert (event price-max ?price-max))
  (assert (menus price-max 0))
  (assert (event ready TRUE))
)

;%%%%%
;%
;% FILTER RULES
;%
;%%%%%

(defrule get-possible-main-courses "Filters forbbiden or impossible main courses"
  (event ready ?)
	(event guests ?guests)
	(event month ?month)
	(event preferred-cuisine-styles $?preferences)
  (event dietary-restrictions $?restrictions)
	=>
	(bind ?main-courses (find-all-instances ((?ins MainCourse))
	(and
    ; Filter non-desired food types
		(or (eq ?preferences (create$ any)) (collection-contains-alo-element ?preferences ?ins:dish-classification))
    ; Filter banned options
    (or (eq ?restrictions (create$ none)) (collection-contains-all-elements ?restrictions ?ins:dish-classification))
		; Filter non available Ingredients
		(all-ingredients-available ?month ?ins:dish-ingredients)
		; Filter difficulty
		(is-easy-enough ?guests ?ins:dish-difficulty)
  )))
	(assert (main-courses ?main-courses))
)

(defrule get-possible-second-courses "Filters forbbiden second courses"
  (event ready ?)
	(event guests ?guests)
	(event month ?month)
	(event preferred-cuisine-styles $?preferences)
  (event dietary-restrictions $?restrictions)
	=>
	(bind ?second-courses (find-all-instances ((?ins SecondCourse))
	(and
    ; Filter non-desired food types
		(or (eq ?preferences (create$ any)) (collection-contains-alo-element ?preferences ?ins:dish-classification))
    ; Filter banned options
    (or (eq ?restrictions (create$ none)) (collection-contains-all-elements ?restrictions ?ins:dish-classification))
		; Filter non available Ingredients
		(all-ingredients-available ?month ?ins:dish-ingredients)
		; Filter difficulty
		(is-easy-enough ?guests ?ins:dish-difficulty)
  )))
	(assert (second-courses ?second-courses))
)

(defrule get-possible-desserts "Filters forbbiden desserts"
  (event ready ?)
	(event guests ?guests)
	(event month ?month)
	(event preferred-cuisine-styles $?preferences)
  (event dietary-restrictions $?restrictions)
	=>
	(bind ?desserts (find-all-instances ((?ins Dessert))
		(and
			; Filter non-desired food types
			(or (eq ?preferences (create$ any)) (collection-contains-alo-element ?preferences ?ins:dish-classification))
	    ; Filter banned options
	    (or (eq ?restrictions (create$ none)) (collection-contains-all-elements ?restrictions ?ins:dish-classification))
			; Filter non available Ingredients
			(all-ingredients-available ?month ?ins:dish-ingredients)
			; Filter difficulty
			(is-easy-enough ?guests ?ins:dish-difficulty)
	)))
	(assert (desserts ?desserts))
)

(defrule get-possible-drink "Filters forbbiden drinks"
  (event ready ?)
	(event drink-types $?drink-types)
  =>
  (bind ?drinks (find-all-instances((?ins Drink))
  	; Filter non-desired drink types
		(or (eq ?drink-types (create$ none)) (not (collection-contains-alo-element ?drink-types ?ins:drink-classification)))
	))
	(bind ?main-drinks (create$))
	(bind ?second-drinks (create$))
	(bind ?dessert-drinks (create$))
	(bind ?general-drinks (create$))
	(loop-for-count (?i 1 (length$ ?drinks)) do
		(progn$ (?type (send (nth$ ?i ?drinks) get-drink-type))
			(switch ?type
				(case M then (bind ?main-drinks (insert$ ?main-drinks (+ (length$ ?main-drinks) 1) (nth$ ?i ?drinks))))
				(case S then (bind ?second-drinks (insert$ ?second-drinks (+ (length$ ?second-drinks) 1) (nth$ ?i ?drinks))))
				(case D then (bind ?dessert-drinks (insert$ ?dessert-drinks (+ (length$ ?dessert-drinks) 1) (nth$ ?i ?drinks))))
				(case G then (bind ?general-drinks (insert$ ?general-drinks (+ (length$ ?general-drinks) 1) (nth$ ?i ?drinks))))
			)
		)
	)
	(assert (main-drinks ?main-drinks))
	(assert (second-drinks ?second-drinks))
	(assert (dessert-drinks ?dessert-drinks))
	(assert (general-drinks ?general-drinks))
)

;%%%%%
;%
;% RECOMENDATION RULES
;%
;%%%%%

(defrule generate-menu-with-main "Creates menu fact with first course"
  (declare (salience -11))
	(main-courses $?main-courses)
	=>
	(loop-for-count (?i 1 (length$ ?main-courses)) do
		(assert (generated-menu (nth$ ?i ?main-courses)))
	)
)

(defrule add-second-to-menu "Adds fact with first and second courses"
  (declare (salience -11))
	(second-courses $?second-courses)
	?gm <- (generated-menu ?main)
	=>
  (loop-for-count (?i 1 (length$ ?second-courses)) do
		(if (are-different-and-combine ?main (nth$ ?i ?second-courses)) then
			(assert (generated-menu ?main (nth$ ?i ?second-courses)))
		)
	)
	(retract ?gm)
)

(defrule add-dessert-to-menu "Adds fact with first course, second course and dessert"
  (declare (salience -11))
	(desserts $?desserts)
	?gm <- (generated-menu ?main ?second)
	=>
  (loop-for-count (?i 1 (length$ ?desserts)) do
		(if (are-different-and-combine ?main (nth$ ?i ?desserts)) then
			(assert (generated-menu ?main ?second (nth$ ?i ?desserts)))
		)
	)
	(retract ?gm)
)

(defrule generate-menu-drink "Adds drink to previous menu facts"
  (declare (salience -11))
	(not (event drink-per-dish ?))
	(general-drinks $?drinks)
	?gm <- (generated-menu ?main ?second ?dessert)
	=>
  (loop-for-count (?i 1 (length$ ?drinks)) do
		(if
      (and
        (drink-combine (nth$ ?i ?drinks) ?main)
        (drink-combine (nth$ ?i ?drinks) ?second)
        (drink-combine (nth$ ?i ?drinks) ?dessert)
      ) then
      (assert (generated-menu ?main ?second ?dessert (nth$ ?i ?drinks)))
    )
	)
	(retract ?gm)
)

(defrule generate-menu-main-drink ""
  (declare (salience -11))
	(event drink-per-dish ?)
	(main-drinks $?drinks)
	?gm <- (generated-menu ?main ?second ?dessert)
	=>
	(loop-for-count (?i 1 (length$ ?drinks)) do
    (if (drink-combine (nth$ ?i ?drinks) ?main) then
		  (assert (generated-menu ?main ?second ?dessert (nth$ ?i ?drinks)))
    )
	)
  (retract ?gm)
)

(defrule generate-menu-second-drink ""
  (declare (salience -11))
	(event drink-per-dish ?)
	(second-drinks $?drinks)
	?gm <- (generated-menu ?main ?second ?dessert ?main-drink)
	=>
	(loop-for-count (?i 1 (length$ ?drinks)) do
    (if (drink-combine (nth$ ?i ?drinks) ?second) then
		  (assert (generated-menu ?main ?second ?dessert ?main-drink (nth$ ?i ?drinks)))
    )
	)
	(retract ?gm)
)

(defrule generate-menu-dessert-drink ""
  (declare (salience -11))
	(event drink-per-dish ?)
	(event drink-per-dish ?)
	(dessert-drinks $?drinks)
	?gm <- (generated-menu ?main ?second ?dessert ?main-drink ?second-drink)
	=>
	(loop-for-count (?i 1 (length$ ?drinks)) do
    (if (drink-combine (nth$ ?i ?drinks) ?dessert) then
		  (assert (generated-menu ?main ?second ?dessert ?main-drink ?second-drink (nth$ ?i ?drinks)))
    )
	)
  (retract ?gm)
)

(defrule validate-general-menu-familiar ""
  (declare (salience -11))
  (not (event drink-per-dish ?))
  ?ef <- (event familiar ?)
  ?pm <- (menus price-max ?menu-max)
  ?gm <- (generated-menu ?main ?second ?dessert ?drink)
  =>
  (bind ?total-price (+ (calculate-price-dishes ?main ?second ?dessert) (calculate-price-drinks ?drink)))
  (bind ?ins
    (make-instance (gensym) of Menu
      (main-course ?main)
      (second-course ?second)
      (dessert ?dessert)
      (menu-drink ?drink)
      (menu-price ?total-price)
    )
  )
  (if (acceptable-for-kids ?ins) then
    (retract ?ef)
    (assert (event child-menu ?ins))
    (send ?ins put-menu-score 0)
  else
    (send ?ins put-menu-score (calculate-menu-score ?ins))
  )
  (if (> ?total-price ?menu-max) then
    (retract ?pm)
    (assert (menus price-max ?total-price))
  )
  (retract ?gm)
)

(defrule validate-general-menu ""
  (declare (salience -11))
	(not (event drink-per-dish ?))
  (not (event familiar ?))
  ?pm <- (menus price-max ?menu-max)
	?gm <- (generated-menu ?main ?second ?dessert ?drink)
	=>
	(bind ?total-price (+ (calculate-price-dishes ?main ?second ?dessert) (calculate-price-drinks ?drink)))
	(bind ?ins
		(make-instance (gensym) of Menu
			(main-course ?main)
			(second-course ?second)
			(dessert ?dessert)
			(menu-drink ?drink)
			(menu-price ?total-price)
		)
	)
  (if (> ?total-price ?menu-max) then
    (retract ?pm)
    (assert (menus price-max ?total-price))
  )
	(send ?ins put-menu-score (calculate-menu-score ?ins))
	(retract ?gm)
)

(defrule validate-drink-per-dish-menu-familiar ""
  (declare (salience -11))
  (event drink-per-dish ?)
  ?ef <- (event familiar ?)
  ?gm <- (generated-menu ?main ?second ?dessert ?main-drink ?second-drink ?dessert-drink)
  =>
  (bind ?drink (nth$ (+ (mod (random) 3) 1) (create$ ?main-drink ?second-drink ?dessert-drink)))
  (bind ?total-price (+ (calculate-price-dishes ?main ?second ?dessert) (calculate-price-drinks ?drink)))
  (bind ?ins
    (make-instance (gensym) of Menu
      (main-course ?main)
      (second-course ?second)
      (dessert ?dessert)
      (menu-drink ?drink)
      (menu-price ?total-price)
    )
  )
  (if (acceptable-for-kids ?ins) then
    (retract ?ef)
    (assert (printable-menu child-data
      (send ?ins get-main-course)
      (send ?ins get-second-course)
      (send ?ins get-dessert)
      (send ?ins get-menu-drink)
      (send ?ins get-menu-price)
    ))
  )
  (send ?ins delete)
)

(defrule validate-drink-per-dish-menu ""
	(declare (salience -11))
  (event drink-per-dish ?)
	(event price-min ?price-min)
	(event price-max ?price-max)
  (event dietary-restrictions $?restrictions)
  (event preferred-cuisine-styles $?preferences)
  ?pm <- (menus price-max ?menu-max)
	?gm <- (generated-menu ?main ?second ?dessert ?main-drink ?second-drink ?dessert-drink)
	=>
	(bind ?food-price (calculate-price-dishes ?main ?second ?dessert))
	(bind ?drinks-price (calculate-price-drinks ?main-drink ?second-drink ?dessert-drink))
	(bind ?total-price (+ ?drinks-price ?food-price))
	(bind ?ins
		(make-instance (gensym) of Menu
			(main-course ?main)
			(main-course-drink ?main-drink)
			(second-course ?second)
			(second-course-drink ?second-drink)
			(dessert ?dessert)
			(dessert-drink ?dessert-drink)
			(menu-price ?total-price)
		)
	)
  (bind ?factor-res (length$ ?restrictions))
  (bind ?factor-pre (length$ ?preferences))
  (if (eq (nth$ 1 ?restrictions) none)
    then (bind ?factor-res 0)
    else (bind ?factor-res (* 30 ?factor-res)))
  (if (eq (nth$ 1 ?preferences) any)
    then (bind ?factor-pre 0)
    else (bind ?factor-pre (* 2 (- 12 ?factor-pre))))
  (bind ?score (calculate-menu-score ?ins))
  (if (< ?score (max (- 55 ?factor-res ?factor-pre) 0))
    then (send ?ins delete)
    else
      (if (> ?total-price ?menu-max) then
        (retract ?pm)
        (assert (menus price-max ?total-price))
        (send ?ins put-menu-score ?score)
      )
	)
	(retract ?gm)
)

(defrule check-generated-menus "Checks if enough menus generated"
  (declare (salience -12))
	(not (generated-menu ? ? ? ?))
  (not (generated-menu ? ? ? ? ? ?))
  =>

  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
	(if (>= (length$ ?menus) 3) then
		(assert (generated-menus low-menu TRUE))
		(assert (generated-menus medium-menu TRUE))
		(assert (generated-menus high-menu TRUE))
	else
		(printout t "| Not enough matching dishes to generate 3 different menus." crlf)
		(if (= (length$ ?menus) 0) then
			(printout t "*-------------------------------------------------------------------------------------" crlf)
		else
			(printout t "| Generated menus will be listed below." crlf)
			(assert (generated-menus all-menus ?menus))
		)
	)
)

(defrule generate-low-price-menu "Generate low price menu"
  (event price-min ?price-min)
  (not (event drink-per-dish ?))
	(generated-menus low-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?menu (get-menu-valoration ?menus ?price-min FALSE))
  (assert (printable-menu cheap ?menu))
  (punish-menu-repetitions ?menu)
)

(defrule generate-medium-price-menu "Generate medium price menu"
  (event price-min ?price-min)
  (menus price-max ?price-max)
  (not (event drink-per-dish ?))
	(generated-menus medium-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?price-mean (/ (+ ?price-min ?price-max) 2))
  (bind ?menu (get-menu-valoration ?menus ?price-mean FALSE))
  (assert (printable-menu medium ?menu))
  (punish-menu-repetitions ?menu)
)

(defrule generate-high-price-menu "Generates higher price menu"
  (menus price-max ?price-max)
  (not (event drink-per-dish ?))
	(generated-menus high-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?menu (get-menu-valoration ?menus ?price-max FALSE))
  (assert (printable-menu high ?menu))
  (punish-menu-repetitions ?menu)
)


(defrule generate-low-price-menu-dpd "Generate low price menu"
  (event price-min ?price-min)
  (event drink-per-dish ?)
	(generated-menus low-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?menu (get-menu-valoration ?menus ?price-min TRUE))
  (assert (printable-menu cheap ?menu))
  (punish-menu-repetitions-dpd ?menu)
)

(defrule generate-medium-price-menu-dpd "Generate medium price menu"
  (event price-min ?price-min)
  (menus price-max ?price-max)
  (event drink-per-dish ?)
	(generated-menus medium-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?price-mean (/ (+ ?price-min ?price-max) 2))
  (bind ?menu (get-menu-valoration ?menus ?price-mean TRUE))
  (assert (printable-menu medium ?menu))
  (punish-menu-repetitions-dpd ?menu)
)

(defrule generate-high-price-menu-dpd "Generates higher price menu"
  (menus price-max ?price-max)
  (event drink-per-dish ?)
	(generated-menus high-menu ?)
	=>
  (bind ?menus (find-all-instances ((?ins Menu)) TRUE))
  (bind ?menu (get-menu-valoration ?menus ?price-max TRUE))
  (assert (printable-menu high ?menu))
  (punish-menu-repetitions-dpd ?menu)
)

(defrule generate-child-menu ""
  (event child-menu ?menu)
  =>
  (assert (printable-menu child ?menu "Kids menu"))
)

(defrule print-menus-std "Prints normal menus in desired format"
  (declare (salience -13))
  (not (event drink-per-dish ?))
  (printable-menu cheap ?menu1)
  (printable-menu medium ?menu2)
  (printable-menu high ?menu3)
  =>
  (print-sorted-menus ?menu1 ?menu2 ?menu3 FALSE)
)

(defrule print-menus-dpd "Prints menus with a drink for each dish"
  (declare (salience -13))
  (event drink-per-dish ?)
  (printable-menu cheap ?menu1)
  (printable-menu medium ?menu2)
  (printable-menu high ?menu3)
  =>
  (print-sorted-menus ?menu1 ?menu2 ?menu3 TRUE)
)

(defrule print-child-menu ""
  (declare (salience -14))
  (printable-menu child ?menu ?header)
  =>
  (print-menu ?menu ?header FALSE)
)

(defrule print-child-menu-dpd ""
  (declare (salience -14))
  (printable-menu child-data ?main ?second ?dessert ?drink ?price)
  =>
  (bind ?menu
    (make-instance (gensym) of Menu
      (main-course ?main)
      (second-course ?second)
      (dessert ?dessert)
      (menu-drink ?drink)
      (menu-price ?price)
    )
  )
  (print-menu ?menu "Kids menu" FALSE)
)

(defrule print-all-menus ""
  (declare (salience -14))
  (not (event drink-per-dish ?))
  (generated-menus all-menus $?menus)
  =>
  (loop-for-count (?i 1 (length$ ?menus)) do
    (print-menu (nth$ ?i ?menus) "Menu" FALSE)
  )
)

(defrule print-all-menus-dpd ""
  (declare (salience -14))
  (event drink-per-dish ?)
  (generated-menus all-menus $?menus)
  =>
  (loop-for-count (?i 1 (length$ ?menus)) do
    (print-menu (nth$ ?i ?menus) "Menu" TRUE)
  )
)

(defrule print-bon-appetit "Elegant ASCII draw"
	(declare (salience -15))
	=>
	(printout t "|                  ___/___/" crlf)
  (printout t "|                  \\,/ \\,/" crlf)
	(printout t "|                   |   |" crlf)
	(printout t "|                 __|___|__" crlf)
	(printout t "|                [_________]" crlf)
	(printout t "|       ,,,,,,      _|//" crlf)
	(printout t "|       , , ::       | /" crlf)
	(printout t "|       <    D        =o" crlf)
	(printout t "|       |.   /       /\\|" crlf)
	(printout t "|   _____|><|_______/o /" crlf)
	(printout t "|  / '==| :: |=='  <  /" crlf)
	(printout t "| /  \\  <    >  /____/" crlf)
	(printout t "|/  _/\\ | :: | /" crlf)
	(printout t "*-------------------------------------------------------------------------------------" crlf)
)
