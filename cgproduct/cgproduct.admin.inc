<?php


function _cgproduct_settings_page() {
  return 'settings page';

}

function _cgproduct_settings_form() {
  $form = array();
  $form['welcome'] = array(
    '#markup' => ('<h1>Welcome to '. t('Product @upload', array('@upload' => 'upload')).'</h1>')
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Product name'),
    '#default_value' => variable_get('title_value'),

  );


  $form['enable'] = array(
    '#title' => t('Enable Product'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('enable_value'),
    //'#default_value' => FALSE,
  );

  $form['image'] = array(
       '#type' => 'file',
       '#description' => 'Please upload a image of the product!',
       '#title' => ('display '. t('Product @img', array('@img' => 'img'))),
       //'#title' => 'Image',
    );

	$form['color'] = array(
    '#type' => 'select',
    '#title' =>t('Product @color', array('@color' => 'aka')),
    '#description' => 'Choose an Color.',
    '#default_value' => variable_get('color_value'),

    '#options' => array(
      1 => 'Red',
      2 => 'Green',
      3 => 'Blue',
    )
  );

  $form['type'] = array(
   '#type' => 'radios',
   '#title' =>(l('Product', 'product/ipad' ).'<br>'.l('Product2', 'product/ipad' ).'<br>'.l('pro3','node/24')),
   '#description' => 'Choose only one option.',
   '#default_value' => variable_get('type_value'),

    '#options' => array(
      1 => 'Toys',
      2 => 'Tools',
    )
  );

  $form['ToID']=array(
    '#type' => 'textfield',
    '#title'=> 'to email address',
    '#description'=>'pls enter your email id',
    '#default_value' => variable_get('toid_value'),

);

  $form['FromID']=array(
    '#type' => 'textfield',
    '#title'=> 'from email address',
    '#description'=>'pls enter receivers email id',
    '#default_value' => variable_get('fromid_value'),


);
  $form['body']=array(
    '#type' => 'textarea',
    '#title'=>'body of mail',
    '#description'=>'pls enter necessary details',
    '#default_value' => variable_get('body_value'),


);

  $form['header_bcc']=array(
    '#type' => 'textfield',
    '#title'=> 'header_bcc',
    '#description'=>'pls enter header_bcc',
    '#default_value' =>variable_get('header_bcc_value'),


);
  $form['header_cc']=array(
    '#type' => 'textfield',
    '#title'=> 'header_cc',
    '#description'=>'pls enter header_cc',
    '#default_value' => variable_get('header_cc_value'),


);
  $form['subject']=array(
    '#type' => 'textfield',
    '#title'=> 'subject',
    '#description'=>'pls enter the subject',
    '#default_value' => variable_get('subject_value'),


);
  $form['description'] = array(
    '#title' => t('Product description'),
    '#type' => 'textarea',
    '#markup' => ('Write'. t('Product @description', array('@description' => 'description'))),
    '#default_value' => variable_get('description_value'),

    '#rows' => 10,
    '#cols' => 60,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  return $form;
}


function _cgproduct_settings_form_validate($form, &$form_state) {

// if (!is_($form_state['values']['title'])) {
//     form_set_error('title', 'Expectings an integer value for Title');
//   }

}

function _cgproduct_settings_form_submit($form, &$form_state){
  // Extenstion should be jpg
  // Size less than 2 MB
  // File should be a valid image
  // Name lenth less than 10 chars
  global $user;
  $body = $form_state['values']['body'];
  $to = $form_state['values']['ToID'];
  $from = $form_state['values']['FromID'];

  $header_bcc = $form_state['values']['header_bcc'];
  $header_cc = $form_state['values']['header_cc'];
  $subject = $form_state['values']['subject'];

    variable_set('body_value', $form_state['values']['body']);
  variable_set('toid_value', $form_state['values']['ToID']);
  variable_set('fromid_value', $form_state['values']['FromID']);
  variable_set('header_bcc_value', $form_state['values']['header_bcc']);
  variable_set('header_cc_value', $form_state['values']['header_cc']);
  variable_set('subject_value', $form_state['values']['subject']);

  // $message = drupal_mail('cgproduct', 'Sent by cgproduct');

    // $message = drupal_mail( 'cgproduct' . '_' . 'cgkey','cgproduct', 'cgproduct_key', $to, user_preferred_language($user), array('body' => $body, 'subject' => $subject, 'headers' => array('Cc' => $header_cc, 'Bcc' => $header_bcc), $from, TRUE));
    $message = drupal_mail( 'cgproduct', 'key', $to, user_preferred_language($user), array('body' => $body, 'subject' => $subject, 'headers' => array('Cc' => $header_cc, 'Bcc' => $header_bcc)), $from, TRUE);


   if($message['result'])
   {
    dsm('sent successfully');
   }
   else
   {
      dsm('mail not sent');
   }




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

 	variable_set('title_value', $form_state['values']['title']);
	variable_set('enable_value', $form_state['values']['enable']);
	variable_set('image_value', $form_state['values']['image']);
	variable_set('color_value', $form_state['values']['color']);
	variable_set('type_value', $form_state['values']['type']);
	variable_set('description_value', $form_state['values']['description']);

  insert_data();

  $name =$form_state['values']['title'];
  $enable =$form_state['values']['enable'];
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

  $nid = db_insert('product')
  ->fields(array(
    'pname' => $name,
    'penable' => $enable,
    'pcolor' => $color,
    'ptype' => $type,
    'pdescription' => $description,
  ))
  ->execute();

}

function insert_data(){



}
function cgproduct_xyz_settings($form_state) {
  $form['cgproduct_xyz_settings_enable'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable a setting',
    '#default_value' => variable_get('cgproduct_xyz_settings_enable'),
  );
  $form['cgproduct_xyz_settings_url'] = array(
    '#type' => 'textfield',
    '#title' => 'URL',
    '#default_value' => variable_get('cgproduct_xyz_settings_url'),
  );
  return system_settings_form($form);
}

