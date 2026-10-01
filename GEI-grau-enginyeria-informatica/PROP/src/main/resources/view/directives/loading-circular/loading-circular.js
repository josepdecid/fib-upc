(function () {
    'use strict';

    /**
     * @ngdoc directive
     * @name project.directives.directive:LoadingCircular
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('LoadingCircularCtrl', LoadingCircularCtrl)
        .directive('loadingCircular', loadingCircular);

    function LoadingCircularCtrl() {
        var vm = this;
        vm.ctrlName = 'LoadingCircularCtrl';
    }

    function loadingCircular() {
        return {
            restrict: 'EA',
            templateUrl: 'directives/loading-circular/loading-circular.tpl.html',
            scope: {
                isRequesting: '=ngModel'
            },
            link: function (scope) {
            }
        };
    }

}());