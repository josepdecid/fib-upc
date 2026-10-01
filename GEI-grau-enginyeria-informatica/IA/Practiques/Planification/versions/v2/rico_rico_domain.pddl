 (define (domain ricoRico)
  (:requirements :strips :typing :adl :equality)
  (:types
    day - object
    dish - object
    category - object
    mainCourse - dish secondCourse - dish
  )

  (:predicates
    (incompatible ?mc - mainCourse ?sc - secondCourse)
    (assignedMC ?d - day ?mc - mainCourse)
    (mainReady ?d - day)
    (secondReady ?d - day)
    (used ?d - dish)
    (classified ?d - dish ?c - category)
    (dayMCClassif ?d - day ?c - category)
    (daySCClassif ?d - day ?c - category)
    (dayBefore ?db - day ?d - day)
  )

  (:action assignMC
    :parameters (?d - day ?mc - mainCourse)
    :precondition (and
      (not (mainReady ?d)) (not (used ?mc))
      (exists (?db - day ?c2 - category) (and (dayBefore ?db ?d) (secondReady ?db) (dayMCClassif ?db ?c2) (not (classified ?mc ?c2))))
    )
    :effect (and
      (used ?mc) (mainReady ?d) (assignedMC ?d ?mc) (forall (?c - category) (when (classified ?mc ?c) (dayMCClassif ?d ?c)))
    )
  )

  (:action assignSC
    :parameters (?d - day ?mc - mainCourse ?sc - secondCourse)
    :precondition (and
      (assignedMC ?d ?mc) (not (secondReady ?d)) (not (used ?sc)) (not (incompatible ?mc ?sc))
      (exists (?db - day ?c2 - category) (and (dayBefore ?db ?d) (secondReady ?db) (daySCClassif ?db ?c2) (not (classified ?sc ?c2))))
    )
    :effect (and
      (used ?sc) (secondReady ?d) (forall (?c - category) (when (classified ?sc ?c) (daySCClassif ?d ?c)))
    )
  )

)
