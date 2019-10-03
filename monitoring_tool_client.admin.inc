<?php

/**
 * @file
 * Administrative functions for the Monitoring tool client.
 */

/**
 * Will return the settings_form.
 *
 * @param array $form
 *   Drupal form.
 * @param array $form_state
 *   Drupal form state.
 *
 * @return array
 *   Drupal form.
 */
function monitoring_tool_client_settings_form(array $form, array &$form_state) {
  $config = variable_get(MONITORING_TOOL_CLIENT_SETTINGS);

  form_load_include($form_state, 'inc', 'monitoring_tool_client', 'admin');

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
  );

  $form['general']['use_webhook'] = array(
    '#type' => 'checkbox',
    '#parents' => array('use_webhook'),
    '#title' => t('Use WebHook'),
    '#default_value' => $config['use_webhook'],
  );

  $form['general']['report_interval'] = array(
    '#type' => 'select',
    '#parents' => array('report_interval'),
    '#title' => t('Send the report'),
    '#description' => t('How often need to send the report'),
    '#default_value' => $config['report_interval'],
    '#options' => array(
      0 => t('Cron execution'),
      3600 => t('1 hour'),
      10800 => t('3 hours'),
      21600 => t('6 hours'),
      32400 => t('9 hours'),
      43200 => t('12 hours'),
      86400 => t('1 day'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="use_webhook"]' => array(
          'checked' => FALSE,
        ),
      ),
    ),
  );

  $form['security'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security'),
  );

  $form['security']['project_id'] = array(
    '#type' => 'textfield',
    '#parents' => array('project_id'),
    '#title' => t('Project ID'),
    '#default_value' => $config['project_id'],
    '#attributes' => array(
      'autocomplete' => 'off',
    ),
  );

  $form['security']['token'] = array(
    '#type' => 'textfield',
    '#parents' => array('secure_token'),
    '#title' => t('Secure token'),
    '#default_value' => $config['secure_token'],
    '#size' => 120,
    '#attributes' => array(
      'autocomplete' => 'off',
    ),
  );

  $form['weak'] = array(
    '#type' => 'fieldset',
    '#title' => t('Weak list'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $modules_options = array();

  foreach (monitoring_tool_client_get_modules() as $machine_name => $info) {
    $modules_options[$machine_name] = $info['name'];
  }

  $form['weak']['modules'] = array(
    '#type' => 'checkboxes',
    '#parents' => array('weak_list'),
    '#title' => t('List of week modules'),
    '#default_value' => $config['weak_list'],
    '#options' => $modules_options,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
  );

  return $form;
}

/**
 * Callback of settings_form.
 *
 * @param array $form
 *   Drupal form.
 * @param array $form_state
 *   Drupal form state.
 */
function monitoring_tool_client_settings_form_submit(array $form, array $form_state) {
  form_state_values_clean($form_state);
  variable_set(MONITORING_TOOL_CLIENT_SETTINGS, $form_state['values']);
  drupal_set_message(t('The configuration options have been saved.'));
}