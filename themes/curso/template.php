<?php

function curso_preprocess_html(&$variables) {
  if (theme_get_setting('fixed')) {
    $variables['classes_array'][] = 'contendor-fijo';
  }
}

function curso_preprocess_catalogo_bloque(&$variables) {
  $variables['catalogo_desc_corta'] = 'Etejo';
}