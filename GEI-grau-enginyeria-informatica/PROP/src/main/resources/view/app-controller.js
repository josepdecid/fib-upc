(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.controller:AppCtrl
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('AppCtrl', AppCtrl);

    function AppCtrl($rootScope, $scope) {
        var vm = this;
        vm.ctrlName = 'AppCtrl';

        $scope.$watch(function () {
            return $rootScope.selectedTheme;
        }, function () {
            vm.selectedTheme = $rootScope.selectedTheme;
        });

        $rootScope.selectedTheme = 'light';

        // Uncomment if wanna test in browser
        //alert('Error loading main backend service, stub activated instead');
        //$rootScope.backendService = backendServiceStub;

        $rootScope.backendService = backendService;

        $rootScope.resetToolbar = function(){
            $rootScope.toolbarParams.title = "";
            $rootScope.toolbarParams.goback = false;
            $rootScope.toolbarParams.search = false;
            $rootScope.toolbarParams.print = false;
            $rootScope.toolbarParams.create = false;
            $rootScope.toolbarParams.import = false;
            $rootScope.toolbarParams.google = false;
            $rootScope.toolbarParams.openExternalTool = false;
            $rootScope.toolbarFunctions.back = function(){};
            $rootScope.toolbarFunctions.search = function(){};
            $rootScope.toolbarFunctions.print = function(){};
            $rootScope.toolbarFunctions.create = function(){};
            $rootScope.toolbarFunctions.import = function(){};
            $rootScope.toolbarFunctions.google = function(){};
            $rootScope.toolbarFunctions.amazon = function(){};
            $rootScope.toolbarFunctions.sharemail = function(){};
            $rootScope.toolbarFunctions.openExternalTool = function(){};
        };

        $rootScope.toolbarParams = {
            'enabled': false,
            'title': "",
            'back': false,
            'search': false,
            'print': false,
            'create': false,
            'import': false,
            'google': false,
            'external': false
        };

        $rootScope.toolbarFunctions = {
            'goback': function(){},
            'search': function(){},
            'print': function(){},
            'create': function(){},
            'import': function(){},
            'google': function(){},
            'amazon': function(){},
            'sharemail': function(){},
            'external': function(){}
        };

    }

}());