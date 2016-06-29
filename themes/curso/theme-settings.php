<?php

function curso_form_system_theme_settings_alter(&$form, $form_state) {

  $form['curso_config'] = array(
    '#type' => 'fieldset',
    '#title' => 'Configuración avanzada del tema',
    '#weight' => -10
  );

  $form['curso_config']['fixed'] = array(
    '#type' => 'select',
    '#title' => 'Contenedor de tamaño fijo',
    '#options' => array(
      0 => 'No',
      1 => 'Si',
    ),
    '#default_value' => theme_get_setting('fixed')
  );

}
