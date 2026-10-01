(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.theme:Themes
     *
     * @description
     *
     */
    angular
        .module('project')
        .config(['$mdThemingProvider', '$provide', function ($mdThemingProvider, $provide) {

            /*

            // THEME 1

            var customPrimaryLight = {
                '50': '#0F3F5C',
                '100': '#0F3F5C',
                '200': '#0F3F5C',
                '300': '#0F3F5C',
                '400': '#0F3F5C',
                '500': '#0F3F5C',
                '600': '#0F3F5C',
                '700': '#0F3F5C',
                '800': '#0F3F5C',
                '900': '#0F3F5C',
                'A100': '#0F3F5C',
                'A200': '#0F3F5C',
                'A400': '#0F3F5C',
                'A700': '#0F3F5C'
            };
            $mdThemingProvider.definePalette('customPrimaryLight',customPrimaryLight);

            var customAccentLight = {
                '50': '#28502E',
                '100': '#28502E',
                '200': '#28502E',
                '300': '#28502E',
                '400': '#28502E',
                '500': '#28502E',
                '600': '#28502E',
                '700': '#28502E',
                '800': '#28502E',
                '900': '#28502E',
                'A100': '#28502E',
                'A200': '#28502E',
                'A400': '#28502E',
                'A700': '#28502E'
            };
            $mdThemingProvider.definePalette('customAccentLight',customAccentLight);

            var customWarnLight = {
                '50': '#F02D3A',
                '100': '#F02D3A',
                '200': '#F02D3A',
                '300': '#F02D3A',
                '400': '#F02D3A',
                '500': '#F02D3A',
                '600': '#F02D3A',
                '700': '#F02D3A',
                '800': '#F02D3A',
                '900': '#F02D3A',
                'A100': '#F02D3A',
                'A200': '#F02D3A',
                'A400': '#F02D3A',
                'A700': '#F02D3A'
            };
            $mdThemingProvider.definePalette('customWarnLight',customWarnLight);

            var customBackgroundLight = {
                '50': '#EFF6EE',
                '100': '#EFF6EE',
                '200': '#EFF6EE',
                '300': '#EFF6EE',
                '400': '#EFF6EE',
                '500': '#EFF6EE',
                '600': '#EFF6EE',
                '700': '#EFF6EE',
                '800': '#EFF6EE',
                '900': '#EFF6EE',
                'A100': '#EFF6EE',
                'A200': '#EFF6EE',
                'A400': '#EFF6EE',
                'A700': '#EFF6EE'
            };
            $mdThemingProvider.definePalette('customBackgroundLight',customBackgroundLight);


            //THEME 2

            var customPrimaryDark = {
                '50': '#7798AB',
                '100': '#7798AB',
                '200': '#7798AB',
                '300': '#7798AB',
                '400': '#7798AB',
                '500': '#7798AB',
                '600': '#7798AB',
                '700': '#7798AB',
                '800': '#7798AB',
                '900': '#7798AB',
                'A100': '#7798AB',
                'A200': '#7798AB',
                'A400': '#7798AB',
                'A700': '#7798AB'
            };
            $mdThemingProvider.definePalette('customPrimaryDark',customPrimaryDark);

            var customAccentDark = {
                '50': '#F9CB40',
                '100': '#F9CB40',
                '200': '#F9CB40',
                '300': '#F9CB40',
                '400': '#F9CB40',
                '500': '#F9CB40',
                '600': '#F9CB40',
                '700': '#F9CB40',
                '800': '#F9CB40',
                '900': '#F9CB40',
                'A100': '#F9CB40',
                'A200': '#F9CB40',
                'A400': '#F9CB40',
                'A700': '#F9CB40'
            };
            $mdThemingProvider.definePalette('customAccentDark',customAccentDark);

            var customWarnDark = {
                '50': '#FF715B',
                '100': '#FF715B',
                '200': '#FF715B',
                '300': '#FF715B',
                '400': '#FF715B',
                '500': '#FF715B',
                '600': '#FF715B',
                '700': '#FF715B',
                '800': '#FF715B',
                '900': '#FF715B',
                'A100': '#FF715B',
                'A200': '#FF715B',
                'A400': '#FF715B',
                'A700': '#FF715B'
            };
            $mdThemingProvider.definePalette('customWarnDark',customWarnDark);

            var customBackgroundDark = {
                '50': '#4C5B5C',
                '100': '#4C5B5C',
                '200': '#4C5B5C',
                '300': '#4C5B5C',
                '400': '#4C5B5C',
                '500': '#4C5B5C',
                '600': '#4C5B5C',
                '700': '#4C5B5C',
                '800': '#4C5B5C',
                '900': '#4C5B5C',
                'A100': '#4C5B5C',
                'A200': '#4C5B5C',
                'A400': '#4C5B5C',
                'A700': '#4C5B5C'
            };
            $mdThemingProvider.definePalette('customBackgroundDark',customBackgroundDark);

            $mdThemingProvider.theme('light')
                .primaryPalette('customPrimaryLight')
                .accentPalette('customAccentLight')
                .warnPalette('customWarnLight')
                .backgroundPalette('customBackgroundLight');

            $mdThemingProvider.theme('dark')
                .primaryPalette('customPrimaryDark')
                .accentPalette('customAccentDark')
                .warnPalette('customWarnDark')
                .backgroundPalette('customBackgroundDark');
*/
            $mdThemingProvider.theme('light');
            $mdThemingProvider.theme('dark').dark();
            
            $mdThemingProvider.theme('success-toast');
            $mdThemingProvider.theme('error-toast');

            $mdThemingProvider.setDefaultTheme('light');
            $mdThemingProvider.alwaysWatchTheme(true);
            $provide.value('themeProvider', $mdThemingProvider);
        }]);
}());
