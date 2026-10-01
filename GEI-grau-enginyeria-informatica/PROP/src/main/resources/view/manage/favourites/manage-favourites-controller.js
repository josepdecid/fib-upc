(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.manage.controller:ManageFavouritesCtrl
     *
     * @description
     *
     */
    angular
        .module('project.manage')
        .controller('ManageFavouritesCtrl', ManageFavouritesCtrl);

    function ManageFavouritesCtrl($rootScope) {
        var vm = this;
        vm.ctrlName = 'ManageFavouritesCtrl';
        vm.title = 'MENU_MANAGEMENT_FAVOURITES';

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.enabled = true;


        var response = $rootScope.backendService.getCurrentUserFavourites();
        vm.documents = JSON.parse(response);
    }
}());