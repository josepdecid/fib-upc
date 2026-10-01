(function () {
    'use strict';

    /**
     * @ngdoc directive
     * @name project.directives.directive:Toolbar
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('ToolbarCtrl', ToolbarCtrl)
        .directive('toolbar', toolbar);

    function ToolbarCtrl() {
        var vm = this;
        vm.ctrlName = 'ToolbarCtrl';
    }

    function toolbar($rootScope) {
        return {
            restrict: 'EA',
            templateUrl: 'directives/toolbar/toolbar.tpl.html',
            scope: {},
            link: function (scope) {

                scope.params = $rootScope.toolbarParams;
                scope.functions = $rootScope.toolbarFunctions;
                scope.isLoggedIn = $rootScope.isLoggedIn;

                scope.$watch(function() {
                    return $rootScope.isLoggedIn;
                }, function() {
                    scope.isLoggedIn = $rootScope.isLoggedIn;
                }, true);

            }
        };
    }

}());