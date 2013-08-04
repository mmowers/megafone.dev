<?php
/**
 * @file
 * feature_megafone.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function feature_megafone_taxonomy_default_vocabularies() {
  return array(
    'actions' => array(
      'name' => 'Actions',
      'machine_name' => 'actions',
      'description' => 'Defines where content will be posted',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
