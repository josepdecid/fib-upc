(define (problem ricoRico) (:domain ricoRico)
  (:objects
    Mon Tue Wed Thu Fri - day
    Spaghetti_Bolognese Mediterranean_Salad Vegan_Sandwich Mushroom_risotto Guacamole_with_tomatoes Sushi American_burger Broccoli_quiche Kirmizi_Mercimek_Corbasi Chinese_Noodles_With_Vegetables Chana_masala Chinese_tiger_salad Shumai - mainCourse
    Roast_pork_with_prunes Spanish_omelette Paella Tuna_steak Chicken_parmesan Lamb_tagine Couscous_meatloaf Coq_au_vin Mapo_tofu Persian_pie Burrito_pie Spicy_seafood_stew - secondCourse
  )
  (:init
    (incompatible Spaghetti_Bolognese Paella)
    (incompatible Mediterranean_Salad Chicken_parmesan)
    (incompatible Kirmizi_Mercimek_Corbasi Chicken_parmesan)
    (incompatible Vegan_Sandwich Roast_pork_with_prunes)
    (incompatible Mushroom_risotto Couscous_meatloaf)
    (incompatible Guacamole_with_tomatoes Lamb_tagine)
    (incompatible Chinese_Noodles_With_Vegetables Spicy_seafood_stew)
    (incompatible Chinese_tiger_salad Burrito_pie)
    (incompatible Sushi Coq_au_vin)
  )
  (:goal
    (forall (?d - day)
      (dayReady ?d)
    )
  )
)
