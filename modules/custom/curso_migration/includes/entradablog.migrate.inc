<?php

class EntradasBlogMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    // 1. Definir la fuente
    $ruta = drupal_get_path('module', 'curso_migration') . '/data/blog.csv';

    $this->source = new MigrateSourceCSV($ruta, array(), array(
      'header_rows' => 1,
      'delimiter' => ';',
      'embedded_newlines' => TRUE,
    ));

    // 2. Definir el destino
    $this->destination = new MigrateDestinationNode('entrada_de_blog');

    // 3. Mapeo de claves
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'description' => 'Clave entera del CSV'
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );


    // 4. Mapear campos
    $this->addFieldMapping('title', 'titulo');
    $this->addFieldMapping('body', 'contenido');

    $this->addFieldMapping('field_tags', 'tags')
      ->separator(',');
    $this->addFieldMapping('field_tags:create_term')
      ->defaultValue(TRUE);

    $this->addFieldMapping('field_categoria:source_type')
      ->defaultValue('tid');
    $this->addFieldMapping('field_categoria', 'categoria')
      ->sourceMigration(array('categoriesblog'));

    $this->addFieldMapping('field_imagen', 'imagen');
    $this->addFieldMapping('field_imagen:source_dir')
      ->defaultValue(dirname(__FILE__) . '/../data/img');

  }

  public function prepareRow($row) {
    $row->titulo = 'Blog - ' . $row->titulo;
    $row->imagen = FALSE;
    if (file_exists(dirname(__FILE__) . '/../data/img/' . $row->id . '.jpg')) {
      $row->imagen = $row->id . '.jpg';
    }
  }
}

class CategoriesBlogMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $data = drupal_get_path('module', 'curso_migration') . '/data/categorias.csv';
    $columnas = array(
      0 => array('id', 'Identificador de la categoría'),
      1 => array('nombre', 'Nombre de la categoría')
    );

    $this->source = new MigrateSourceCSV($data, $columnas, array(
      'delimiter' => ';',
      'track_changes' => TRUE,
      )
    );

    $this->destination = new MigrateDestinationTerm('categorias');


    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'description' => 'id de la entrada',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $this->addFieldMapping('name', 'nombreMod');
  }

  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $row->nombreMod = ucfirst($row->nombre);

  }
}
