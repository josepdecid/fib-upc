(define (problem ricoRico) (:domain ricoRico)
  (:objects
    Mon Tue Wed Thu Fri DummyD - day
    Spaghetti_Bolognese Mediterranean_Salad Vegan_Sandwich Mushroom_risotto Guacamole_with_tomatoes - mainCourse
    Roast_pork_with_prunes Spanish_omelette Paella Tuna_steak Chicken_parmesan - secondCourse
    Fish Meat Soup Salad Rice Pasta Vegetables DummyC - category
  )
  (:init
    (incompatible Spaghetti_Bolognese Paella)
    (incompatible Mediterranean_Salad Chicken_parmesan)
    (incompatible Vegan_Sandwich Roast_pork_with_prunes)

    ; Main courses
    (classified Spaghetti_Bolognese Pasta)
    (classified Mediterranean_Salad Salad)
    (classified Vegan_Sandwich Vegetables)
    (classified Mushroom_risotto Rice)
    (classified Guacamole_with_tomatoes Vegetables)
    ; Second courses
    (classified Roast_pork_with_prunes Meat)
    (classified Spanish_omelette Meat)
    (classified Paella Rice)
    (classified Tuna_steak Fish)
    (classified Chicken_parmesan Meat)

    (dayBefore DummyD Mon)
    (dayBefore Mon Tue)
    (dayBefore Tue Wed)
    (dayBefore Wed Thu)
    (dayBefore Thu Fri)

    ; Dummy initializations
    (mainReady DummyD)
    (secondReady DummyD)
    (dayMCClassif DummyD DummyC)
    (daySCClassif DummyD DummyC)
  )
  (:goal
    (forall (?d - day)
      (and (mainReady ?d) (secondReady ?d))
    )
  )
)
