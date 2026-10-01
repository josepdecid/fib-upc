(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.settings.controller:SettingsCtrl
     *
     * @description
     *
     */
    angular
        .module('project.settings')
        .controller('SettingsCtrl', SettingsCtrl);

    function SettingsCtrl($rootScope, $scope, $mdDialog, $translate, $state, $filter) {
        var vm = this;
        vm.ctrlName = 'SettingsCtrl';
        vm.title = "MENU_SETTINGS";

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.enabled = true;

        vm.languages = {
            title: 'SETTINGS_LANGUAGES',
            values: [
                {
                    name: 'LANG_ENGLISH',
                    flag: 'flag-eng',
                    locale: 'en_US',
                    selected: false
                },
                {
                    name: 'LANG_CATALAN',
                    flag: 'flag-cat',
                    locale: 'ca_ES',
                    selected: false
                },
                {
                    name: 'LANG_SPANISH',
                    flag: 'flag-esp',
                    locale: 'es_ES',
                    selected: false
                }
            ]
        };

        angular.forEach(vm.languages.values, function (language) {
            language.selected = (language.locale === $translate.use());
        });

        vm.theme = {
            title: 'SETTINGS_THEME',
            themeDark: 'SWITCH_THEME_DARK',
            themeLight: 'SWITCH_THEME_LIGHT',
            darkTheme: $rootScope.selectedTheme === 'dark'
        };

        vm.disableOtherLanguages = function (value) {
            angular.forEach(vm.languages.values, function (language) {
                language.selected = false;
            });
            $translate.use(value.locale);
        };

        vm.deleteAccount = function (event) {
            var translations = {
                title: $filter('translate')('DIALOG_DELETE_TITLE'),
                textContent: $filter('translate')('DIALOG_DELETE_CONTENT'),
                ariaLabel: $filter('translate')('DIALOG_DELETE_ARIA_LABEL'),
                ok: $filter('translate')('DIALOG_DELETE_OK'),
                cancel: $filter('translate')('DIALOG_DELETE_CANCEL')
            };

            var confirm = $mdDialog.confirm()
                .title(translations.title)
                .textContent(translations.textContent)
                .ariaLabel(translations.ariaLabel)
                .targetEvent(event)
                .ok(translations.ok)
                .cancel(translations.cancel);

            $mdDialog.show(confirm).then(function() {
                $rootScope.backendService.userDelete();
                $rootScope.isLoggedIn = false;
                $state.go('project');
            }, function() {
            });
        };

        $scope.$watch('vm.theme.darkTheme', function () {
            $rootScope.selectedTheme = vm.theme.darkTheme ? 'dark' : 'light';
        });
    }

}());