(function () {
    'use strict';

    /**
     * @ngdoc component
     * @name project.directives.directive:FileSelect
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('FileSelectCtrl', FileSelectCtrl)
        .directive("fileSelect", fileSelect);

    function FileSelectCtrl() {
        var vm = this;
        vm.ctrlName = 'FileSelectCtrl';
    }

    function fileSelect() {
        return {
            link: function($scope, element) {
                element.bind("change", function(event){
                    $scope.file = (event.srcElement || event.target).files[0];
                    $scope.getFile();
                });
            }
        }
    }

}());