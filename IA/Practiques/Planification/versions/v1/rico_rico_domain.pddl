(define (domain ricoRico)
  (:requirements :strips :typing :adl)
  (:types
    day - object
    dish - object
    mainCourse - dish secondCourse - dish
  )

  (:predicates
    (incompatible ?mc - mainCourse ?sc - secondCourse)
    (assignedMC ?d - day ?mc - mainCourse)
    (assignedSC ?d - day ?sc - secondCourse)
    (mainReady ?d - day)
    (secondReady ?d - day)
    (used ?d - dish)
  )

  (:action assignMC
    :parameters (?d -day ?mc - mainCourse)
    :precondition (and (not (mainReady ?d)) (not (used ?mc)))
    :effect (and (assignedMC ?d ?mc) (used ?mc) (mainReady ?d))
  )

  (:action assignSC
    :parameters (?d - day ?mc - mainCourse ?sc - secondCourse)
    :precondition (and (assignedMC ?d ?mc)  (not (secondReady ?d)) (not (used ?sc)) (not (incompatible ?mc ?sc)))
    :effect (and (assignedSC ?d ?sc) (used ?sc) (secondReady ?d))
  )
)
