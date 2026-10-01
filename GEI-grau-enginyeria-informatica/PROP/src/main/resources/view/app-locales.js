(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.locale:Locales
     *
     * @description
     *
     */
    angular
        .module('project')
        .config(['$translateProvider', function ($translateProvider) {
            $translateProvider.useStaticFilesLoader({
                prefix: 'res/locales/locale-',
                suffix: '.json'
            });

            //Languages accepted: en_US, ca_ES and es_ES
            $translateProvider.preferredLanguage('en_US');
            $translateProvider.useSanitizeValueStrategy(null);
        }]);
}());

