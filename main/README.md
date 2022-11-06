# Partitioned-Hash-Join

Το πρόγραμμα χωρίζεται σε δύο φάσεις:

1) Partition-phase
2) Hopscotch

Partition-phase:
  Part : struct με Relation και το PrefixSum του.

  Σε αυτή τη φάση η PartitionedHashJoin.Solve καλεί την PartitionRec η οποία
  πρώτα σπάει με την κλάση Partition το Relation σε μικρότερα Relation με το
  PrefixSum (Parts) και για κάθε ένα αναδρομικά το ξανασπάει.

  Όταν φτάσει στο τελευταίο στάδιο Partitioning καλεί την Merge η οποία ενώνει
  τα Parts σε έναν ενιαίο πίνακα Relation και έναν PrefixSum.

  Η Partition παίρνει σαν ορίσματα το Relation το Ν το from και to. Το from
  και to είναι για να καθορίσουν πιο κομμάτι του Relation μας ενδιαφέρει για
  partitioning. Κατα το PartitionRec δίνεται αναδρομικά όλο το ρελατιον και
  στα from to τα index από το PrefixSum.

Hopscotch:
