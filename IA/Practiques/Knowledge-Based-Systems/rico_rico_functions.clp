;%%%%%
;%
;% DEFINITIONS
;%
;%%%%%

(defglobal
  ?*EVENT_TYPES* = (create$ Familiar Congress)
  ?*DRINK_TYPES* = (create$ Alcohol Soft-drinks Caffeine Juice none)
  ?*CUISINE_STYLES* = (create$ Mediterranean Spanish Italian French Chinese Japanese Turkish American Mexican Indian Moroccan Gourmet any)
  ?*DIETARY_RESTRICTIONS* = (create$ Gluten-free Vegan Vegetarian Lactose-free Kosher Islamic none)
)

;%%%%%
;%
;% FUNCTIONS
;%
;%%%%%

(deffunction ask-question-yes-no (?question)
  (printout t "| > " ?question crlf "| ")
  (bind ?answer (read))
  (bind ?allowed-values (create$ Yes No yes no Y N y n))
  (while (not (member$ ?answer ?allowed-values)) do
    (printout t "| > " ?question crlf "| ")
    (bind ?answer (read))
  )
  (if (or (eq ?answer Yes) (eq ?answer yes) (eq ?answer Y) (eq ?answer y))
  then TRUE
  else FALSE
  )
)

(deffunction ask-question-opt (?question ?allowed-values)
  (printout t "| > " ?question ?allowed-values crlf "| ")
  (bind ?answer (read))
  (while (not (member$ ?answer ?allowed-values)) do
    (printout t "| > " ?question crlf "| ")
    (bind ?answer (read))
  )
  ?answer
)

(deffunction ask-question-multi-opt (?question ?allowed-values)
  (printout t "| > " ?question ?allowed-values crlf "| ")
  (bind ?line (readline))
  (bind $?answer (explode$ ?line))
  (bind ?valid FALSE)
  (while (not ?valid) do
    (loop-for-count (?i 1 (length$ $?answer)) do
      (bind ?valid FALSE)
      (bind ?value-belongs FALSE)
      (loop-for-count (?j 1 (length$ $?allowed-values)) do
        (if (eq (nth$ ?i $?answer) (nth$ ?j $?allowed-values)) then
          (bind ?value-belongs TRUE)
          (break)
        )
      )
      (if (not ?value-belongs) then
        (printout t "| > " (nth$ ?i $?answer) " is not a valid option" crlf)
        (break)
      )
      (bind ?valid TRUE)
    )
    (if ?valid then (break))

    (printout t "| > " ?question crlf "| ")
    (bind ?line (readline))
    (bind $?answer (explode$ ?line))
  )
  $?answer
)

(deffunction ask-question-date-format (?question)
  (printout t "| > " ?question crlf "| ")
  (while TRUE do
    (bind ?date (readline))
    (bind $?answer (explode$ ?date))
    (if (not (eq (length$ ?answer) 2)) then
      (printout t "| > Incorrect format, date should have the format DD MM" crlf "| ")
    else (if (and
      (and (>= (nth$ 1 ?answer) 1) (<= (nth$ 1 ?answer) 31))
      (and (>= (nth$ 2 ?answer) 1) (<= (nth$ 2 ?answer) 12))
    ) then
      (break)
    else
      (printout t "| > Check that date is valid" crlf "| ")
    ))
  )
  ?answer
)

(deffunction is-num (?num)
  (bind ?ret (or (eq (type ?num) INTEGER) (eq (type ?num) FLOAT)))
  ?ret
)

(deffunction ask-question-num (?question ?min ?max)
  (printout t "| > " ?question)
  (bind ?answer (read))
  (while (not (and (is-num ?answer) (>= ?answer ?min) (<= ?answer ?max))) do
    (printout t "| " ?question)
        (bind ?answer (read)))
  ?answer
)

(deffunction collection-contains-alo-element (?elements ?collection)
  (loop-for-count (?i 1 (length$ ?elements)) do
    (loop-for-count (?j 1 (length$ ?collection)) do
      (if (eq (nth$ ?i ?elements) (nth$ ?j ?collection))
      then (return TRUE))
    )
  )
  FALSE
)


(deffunction collection-contains-all-elements (?elements ?collection)
  (loop-for-count (?i 1 (length$ ?elements)) do
    (bind ?found FALSE)
    (loop-for-count (?j 1 (length$ ?collection)) do
      (if (eq (nth$ ?i ?elements) (nth$ ?j ?collection)) then
        (bind ?found TRUE)
        (break)
      )
    )
    (if (not ?found) then (return FALSE))
  )
  TRUE
)

(deffunction calculate-price-drinks ($?elements)
  (bind ?price 0.0)
  (loop-for-count (?i 1 (length$ ?elements))
    (bind ?price (+ ?price (send (nth$ ?i ?elements) get-drink-price)))
  )
  ?price
)

(deffunction calculate-price-dishes ($?elements)
  (bind ?price 0.0)
  (loop-for-count (?i 1 (length$ ?elements))
    (bind ?price (+ ?price (send (nth$ ?i ?elements) get-dish-price)))
  )
  ?price
)

(deffunction are-different-and-combine (?first-dish ?second-dish)
  (if (not (eq (send ?first-dish get-dish-name) (send ?second-dish get-dish-name))) then
    (if (and
      (collection-contains-alo-element (send ?first-dish get-dish-combination) (send ?second-dish get-dish-classification))
      (collection-contains-alo-element (send ?second-dish get-dish-combination) (send ?first-dish get-dish-classification))
    ) then (return TRUE))
  )
  FALSE
)

(deffunction drink-combine (?drink ?dish)
  (if (or
    (eq (send ?drink get-drink-combination) (create$ All))
    (and
      (collection-contains-alo-element (send ?dish get-dish-combination) (send ?drink get-drink-combination))
      (collection-contains-alo-element (send ?drink get-drink-combination) (send ?dish get-dish-combination))
    )
  ) then (return TRUE))
  FALSE
)

(deffunction acceptable-for-kids (?menu)
  (bind ?difficulty
    (+
      (send (send ?menu get-main-course) get-dish-difficulty)
      (send (send ?menu get-second-course) get-dish-difficulty)
      (send (send ?menu get-dessert) get-dish-difficulty)
    )
  )
  (if (> ?difficulty 10) then (return FALSE))
  (bind ?drink-categories (send (send ?menu get-menu-drink) get-drink-classification))
  (if (collection-contains-alo-element (create$ Alcohol Caffeine) ?drink-categories)
    then (return FALSE))
  TRUE
)

(deffunction is-easy-enough (?guests ?dish-difficulty)
  (if (< ?dish-difficulty 4) then
    (return TRUE)
  )
  (<= ?dish-difficulty (- 10 (div ?guests 100)))
)

(deffunction all-ingredients-available (?month ?ingredients)
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?availability (send (nth$ ?i ?ingredients) get-ing-availability))
    (if (and
      (not (member$ 0 ?availability))
      (not (member$ ?month ?availability)))
    then (return FALSE))
  )
  TRUE
)

(deffunction calculate-non-helathy (?ingredient)
  (+
    (/ (send ?ingredient get-calories) 500)
    (/ (send ?ingredient get-fat) 200)
    (/ (send ?ingredient get-cholesterol) 100)
  )
)

(deffunction variety-nutrition (?ingredient)
  (bind ?protein (send ?ingredient get-protein))
  (bind ?fat (send ?ingredient get-fat))
  (bind ?carbohydrates (send ?ingredient get-carbohydrates))
  (bind ?total (+ ?protein ?fat ?carbohydrates))

  (bind ?protein (abs (- 35 (* 100 (/ ?protein ?total)))))
  (bind ?fat (abs (- 25 (* 100 (/ ?fat ?total)))))
  (bind ?carbohydrates (abs (- 45 (* 100 (/ ?carbohydrates ?total)))))

  (/ (+ ?protein ?fat ?carbohydrates) 100)
)

(deffunction heuristic-variety-main-second (?main-classification ?second-classification)
  (bind ?score 40)
  (loop-for-count (?i 1 (length$ ?main-classification))
    (if (member$ (nth$ ?i ?main-classification) ?second-classification) then
      (bind ?score (- ?score 3))
    )
  )
  (max ?score 0)
)

(deffunction heuristic-healthy (?menu) "Decrese the heuristic if the food contains more calories, fats or cholesterol"
  (bind ?score 30)
  (bind ?ingredients (send (send ?menu get-main-course) get-dish-ingredients))
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (calculate-non-helathy (nth$ ?i ?ingredients))))
  )
  (bind ?ingredients (send (send ?menu get-second-course) get-dish-ingredients))
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (calculate-non-helathy (nth$ ?i ?ingredients))))
  )
  (bind ?ingredients (send (send ?menu get-dessert) get-dish-ingredients))
    (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (calculate-non-helathy (nth$ ?i ?ingredients))))
  )
  (max ?score 0)
)

(deffunction heuristic-variety-nutrition (?menu)
  (bind ?score 30)
  (bind ?ingredients (send (send ?menu get-main-course) get-dish-ingredients))
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (variety-nutrition (nth$ ?i ?ingredients))))
  )
  (bind ?ingredients (send (send ?menu get-second-course) get-dish-ingredients))
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (variety-nutrition (nth$ ?i ?ingredients))))
  )
  (bind ?ingredients (send (send ?menu get-dessert) get-dish-ingredients))
  (loop-for-count (?i 1 (length$ ?ingredients)) do
    (bind ?score (- ?score (variety-nutrition (nth$ ?i ?ingredients))))
  )
  (max ?score 0)
)

(deffunction calculate-menu-score (?menu)
  (bind ?main-classification (send (send ?menu get-main-course) get-dish-classification))
  (bind ?second-classification (send (send ?menu get-second-course) get-dish-classification))

  (bind ?heuristic1 (heuristic-variety-main-second ?main-classification ?second-classification))
  (if (< ?heuristic1 10) then (return 0))
  (bind ?heuristic2 (heuristic-healthy ?menu))
  (if (< ?heuristic2 10) then (return 0))
  (return (+ ?heuristic1 ?heuristic2 (heuristic-variety-nutrition ?menu)))
)

(deffunction calculate-menu-priority (?menu ?drink-per-dish)
  (bind ?dishes-priority (+
    (send (send ?menu get-main-course) get-dish-priority)
    (send (send ?menu get-second-course) get-dish-priority)
    (send (send ?menu get-dessert) get-dish-priority)
  ))
  (if (not ?drink-per-dish) then
    (return (+ ?dishes-priority
      (send (send ?menu get-menu-drink) get-drink-priority)
    ))
  else
    (return (+ ?dishes-priority
      (send (send ?menu get-main-course-drink) get-drink-priority)
      (send (send ?menu get-second-course-drink) get-drink-priority)
      (send (send ?menu get-dessert-drink) get-drink-priority)
    ))
  )
)

(deffunction calculate-menu-valoration (?menu ?price-value ?drink-per-dish)
  (bind ?valoration (-
    (abs (- (send ?menu get-menu-price) ?price-value))
    (send ?menu get-menu-score)
    (* -50 (calculate-menu-priority ?menu ?drink-per-dish))
  ))
  (return ?valoration)
)

(deffunction get-menu-valoration (?menus ?price-value ?drink-per-dish)
  (bind ?best-index 1)
  (bind ?best-value (calculate-menu-valoration (nth$ 1 ?menus) ?price-value ?drink-per-dish))
  (loop-for-count (?i 2 (length$ ?menus)) do
    (bind ?value (calculate-menu-valoration (nth$ ?i ?menus) ?price-value ?drink-per-dish))
    (if (< ?value ?best-value) then
      (bind ?best-index ?i)
      (bind ?best-value ?value)
    )
  )
  (nth$ ?best-index ?menus)
)

(deffunction punish-menu-repetitions (?menu)
  (bind ?priority (send (send ?menu get-main-course) get-dish-priority))
  (send (send ?menu get-main-course) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-second-course) get-dish-priority))
  (send (send ?menu get-second-course) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-dessert) get-dish-priority))
  (send (send ?menu get-dessert) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-menu-drink) get-drink-priority))
  (send (send ?menu get-menu-drink) put-drink-priority (+ ?priority 1))
)

(deffunction punish-menu-repetitions-dpd (?menu)
  (bind ?priority (send (send ?menu get-main-course) get-dish-priority))
  (send (send ?menu get-main-course) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-second-course) get-dish-priority))
  (send (send ?menu get-second-course) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-dessert) get-dish-priority))
  (send (send ?menu get-dessert) put-dish-priority (+ ?priority 1))
  (bind ?priority (send (send ?menu get-main-course-drink) get-drink-priority))
  (send (send ?menu get-main-course-drink) put-drink-priority (+ ?priority 2))
  (bind ?priority (send (send ?menu get-second-course-drink) get-drink-priority))
  (send (send ?menu get-second-course-drink) put-drink-priority (+ ?priority 2))
  (bind ?priority (send (send ?menu get-dessert-drink) get-drink-priority))
  (send (send ?menu get-dessert-drink) put-drink-priority (+ ?priority 2))
)

(deffunction print-menu (?menu ?header ?drink-per-dish)
  (if ?drink-per-dish then
    (printout t "*-------------------------------------------------------------------------------------" crlf)
    (printout t "| " ?header crlf)
    (printout t "|-------------------------------------------------------------------------------------" crlf)
    (printout t "| Main course: " (send (send ?menu get-main-course) get-dish-name) "." crlf)
    (printout t "| - Drink: " (send (send ?menu get-main-course-drink) get-drink-name) "." crlf)
    (printout t "| Second course: " (send (send ?menu get-second-course) get-dish-name) "." crlf)
    (printout t "| - Drink: " (send (send ?menu get-second-course-drink) get-drink-name) "." crlf)
    (printout t "| Dessert: " (send (send ?menu get-dessert) get-dish-name) "." crlf)
    (printout t "| - Drink: " (send (send ?menu get-dessert-drink) get-drink-name) "." crlf)
    (printout t "| Price: " (send ?menu get-menu-price) "€" crlf)
    (if (not (= 0 (send ?menu get-menu-score))) then (printout t "| Score: " (send ?menu get-menu-score) "p." crlf))
    (printout t "*-------------------------------------------------------------------------------------" crlf)
  else
    (printout t "*-------------------------------------------------------------------------------------" crlf)
    (printout t "| " ?header crlf)
    (printout t "|-------------------------------------------------------------------------------------" crlf)
    (printout t "| Main course: " (send (send ?menu get-main-course) get-dish-name) "." crlf)
    (printout t "| Second course: " (send (send ?menu get-second-course) get-dish-name) "." crlf)
    (printout t "| Dessert: " (send (send ?menu get-dessert) get-dish-name) "." crlf)
    (printout t "| Drink: " (send (send ?menu get-menu-drink) get-drink-name) "." crlf)
    (printout t "| Price: " (send ?menu get-menu-price) "€" crlf)
    (if (not (= 0 (send ?menu get-menu-score))) then (printout t "| Score: " (send ?menu get-menu-score) "p." crlf))
    (printout t "*-------------------------------------------------------------------------------------" crlf)
  )
)

(deffunction print-sorted-menus (?menu1 ?menu2 ?menu3 ?drink-per-dish)
  (bind ?price1 (send ?menu1 get-menu-price))
  (bind ?price2 (send ?menu2 get-menu-price))
  (bind ?price3 (send ?menu3 get-menu-price))

  (if (and (< ?price1 ?price2) (< ?price1 ?price3)) then
    (print-menu ?menu1 "Cheap menu" ?drink-per-dish)
    (if (< ?price2 ?price3) then
      (print-menu ?menu2 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu3 "Expensive menu" ?drink-per-dish)
    else
      (print-menu ?menu3 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu2 "Expensive menu" ?drink-per-dish)
    )
  )
  (if (and (< ?price2 ?price1) (< ?price2 ?price3)) then
    (print-menu ?menu2 "Cheap menu" ?drink-per-dish)
    (if (< ?price1 ?price3) then
      (print-menu ?menu1 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu3 "Expensive menu" ?drink-per-dish)
    else
      (print-menu ?menu3 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu1 "Expensive menu" ?drink-per-dish)
    )
  )
  (if (and (< ?price3 ?price1) (< ?price3 ?price2)) then
    (print-menu ?menu3 "Cheap menu" ?drink-per-dish)
    (if (< ?price1 ?price2) then
      (print-menu ?menu1 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu2 "Expensive menu" ?drink-per-dish)
    else
      (print-menu ?menu2 "Medium price menu" ?drink-per-dish)
      (print-menu ?menu1 "Expensive menu" ?drink-per-dish)
    )
  )
)
