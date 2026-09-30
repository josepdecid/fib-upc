(define (problem ricoRico) (:domain ricoRico)
  (:objects
    Mon Tue Wed Thu Fri - day
    Spaghetti_Bolognese Mediterranean_Salad - mainCourse
    Roast_pork_with_prunes Spanish_omelette - secondCourse
  )
  (:init
    (incompatible Spaghetti_Bolognese Roast_pork_with_prunes)
    (incompatible Spaghetti_Bolognese Spanish_omelette)
    (incompatible Mediterranean_Salad Roast_pork_with_prunes)
    (incompatible Mediterranean_Salad Spanish_omelette)
  )
  (:goal
    (forall (?d - day)
      (dayReady ?d)
    )
  )
)
