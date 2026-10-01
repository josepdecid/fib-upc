(define (problem ricoRico) (:domain ricoRico)
  (:objects
    Mon Tue Wed Thu Fri - day
    Spaghetti_Bolognese Mediterranean_Salad - mainCourse
    Roast_pork_with_prunes Spanish_omelette - secondCourse
  )
  (:init
    (incompatible Spaghetti_Bolognese Roast_pork_with_prunes)
  )
  (:goal
    (forall (?d - day)
      (dayReady ?d)
    )
  )
)
