<?php
// function pid_load($pid){
//   dsm($pid);
// }

function _cgproduct_update_form($form_id, $form_state, $pid) {
  drupal_add_css(drupal_get_path('module', 'cgproduct').'/css/cgproduct.css');
  drupal_add_css(drupal_get_path('theme', 'procuct_theme').'/cgproduct.css');
  drupal_add_js(drupal_get_path('module', 'cgproduct').'/js/cgproduct.js');
  $form = array();
  dsm($pid);
  //$pi=$pid['as']['pid'];
  dsm($pid['as']['name']);
  //,$pid['as']['name'],$pid['as']['color'],$pid['as']['desc'],$pid['as']['type']);
  $form['pid'] = array(
    '#type' => 'textfield',
    '#title' => t('Product ID'),
    '#default_value' => $pid['as']['pid'],
    '#element_validate' => array('_pid_validate'),

  );


  // $query = db_select('product', 'p')
  //   ->condition('p.pid', $pid, '=')
  //   ->fields('p', array('pid','pname', 'pcolor', 'pdescription', 'ptype'))
  //   ->range(0, 50);

  //   $var = '';
  //   $t_name = '';
  //   $t_color='';
  //   $t_desc='';
  //   $t_type='';

  //   $result = $query->execute();

  //   while($record = $result->fetchAssoc()) {

  //       $t_name = $record['pname'];
  //       $t_color=$record['pcolor'];
  //       $t_desc=$record['pdescription'];
  //       $t_type=$record['ptype'];
  //      //return $record['pname'].'<br>';

  //       //return 'aka';
  //       //'#markup' => 'Product Title:  ';
  //   }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Product name',
    '#default_value' => $pid['as']['name'],

  );

  $form['image'] = array(
       '#type' => 'file',
       '#description' => 'Please upload a image of the product!',
       '#title' => 'Image',
    );
  $options = array(
      'Red' => 1,
      'Green' => 2,
      'Blue' => 3,
  );


  $form['color'] = array(
    '#type' => 'select',
    '#title' =>'Color',
    '#description' => 'Choose an Color.',
    '#default_value' => $options[$pid['as']['color']],

    '#options' => array(
      1 => 'Red',
      2 => 'Green',
      3 => 'Blue',
    )
  );

$options_type = array(
      'Toys' => 1,
      'Tools' => 2,
    );

  $form['type'] = array(
   '#type' => 'radios',
   '#title' =>'Type of product',
   '#description' => 'Choose only one option.',
   '#default_value' => $options_type[$pid['as']['type']],

    '#options' => array(
      1 => 'Toys',
      2 => 'Tools',
    )
  );

  $form['description'] = array(
    '#title' => 'Product description',
    '#type' => 'textarea',
    '#default_value' => $pid['as']['desc'],

    '#rows' => 10,
    '#cols' => 60,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update',
  );

  return $form;
}

function _pid_validate($element, &$form_state, $form) {
  dsm('element validate in cgproduct is being called');
  $val = (int) $element['#value'];

  if ($val == 0) {
    form_error($element, 'Expecting an integer value for Product Id');
  }
}
function _cgproduct_update_form_validate($form, &$form_state) {
  dsm('validate in cgproduct is being called');
}

function _cgproduct_update_form_submit($form, &$form_state){
  dsm('submit handler in cgproduct');
  // Extenstion should be jpg
  // Size less than 2 MB
  // File should be a valid image
  // Name lenth less than 10 chars
  $max_size = 2*1024*1024;
  $validators = array(
    'file_validate_extensions' => array('jpg jpeg'),
    'file_validate_is_image' => array(),
    'file_validate_size' => array($max_size),
  );
  $file = file_save_upload('image', $validators);
  if ($file) {
    $file = file_move($file, 'public://' . $file->filename);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    variable_set('cgproduct_file', $file->fid);
  }




  $pid=$form_state['values']['pid'];
  $name =$form_state['values']['title'];
  //$enable =$form_state['values']['enable'];
  $options = array(
      1 => 'Red',
      2 => 'Green',
      3 => 'Blue',
  );


  $color = $options[$form_state['values']['color']];

  $description = $form_state['values']['description'];

  $options_type = array(
      1 => 'Toys',
      2 => 'Tools',
    );

  $type =$options_type[$form_state['values']['type']];

  // $nid = db_insert('product')
  // ->fields(array(
  //   'pname' => $name,
  //   'penable' => $enable,
  //   'pcolor' => $color,
  //   'ptype' => $type,
  //   'pdescription' => $description,
  // ))

  $nid = db_update('product')
  ->fields(array(
    'pname' => $name,
    'pcolor' => $color,
    'ptype' => $type,
    'pdescription' => $description,
  ))
  ->condition('pid', $pid, '=')
  ->execute();

}

