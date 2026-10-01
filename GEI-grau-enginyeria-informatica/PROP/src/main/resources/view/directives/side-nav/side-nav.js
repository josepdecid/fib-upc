(function () {
    'use strict';

    /**
     * @ngdoc directive
     * @name project.directives.directive:SideNav
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('SideNavController', SideNavCtrl)
        .directive('sideNav', sideNav);

    function SideNavCtrl() {
        var vm = this;
        vm.ctrlName = 'SideNavCtrl';
        vm.title = 'TITLE_PPP';
    }

    function sideNav($rootScope, $mdDialog, menuItems, $state) {
        return {
            restrict: 'EA',
            templateUrl: 'directives/side-nav/side-nav.tpl.html',
            scope: {},
            link: function (scope) {

                scope.userEdit = function(){
                    (function showDialog() {
                        $mdDialog.show({
                            controller: DialogUserImageController,
                            templateUrl: 'directives/side-nav/user-image-dialog.tpl.html',
                            clickOutsideToClose: true,
                            escapeToClose: true
                        })}());

                    function DialogUserImageController($rootScope, $scope) {
                        $scope.avatars = new Array(13);

                        $scope.changeAvatar = function(avatar){
                            $rootScope.currentUser.avatar = avatar;
                            $rootScope.backendService.changeUserAvatar(avatar);
                            $scope.back();
                        };

                        $scope.back = function(){
                            $mdDialog.hide();
                        }
                    }
                };

                scope.logout = function () {
                    $rootScope.backendService.userLogout();
                    $rootScope.isLoggedIn = false;
                    $state.go('project');
                };

                scope.$watch(function() {
                    return $rootScope.isLoggedIn;
                }, function() {
                    scope.isLoggedIn = $rootScope.isLoggedIn;
                    scope.currentUser = $rootScope.currentUser;
                }, true);

                angular.forEach(menuItems, function (item) {
                    item.icon = 'fa-' + item.icon;
                    if (angular.isDefined(item.children)) {
                        angular.forEach(item.children, function (childItem) {
                            childItem.icon = 'fa-' + childItem.icon;
                        })
                    }
                });

                scope.menuItems = menuItems;

                $rootScope.$on('$stateChangeStart', function(event, toState) {
                    $mdDialog.hide();

                    angular.forEach(menuItems, function (item) {
                        item.selected = item.state === toState.name;
                        item.collapsed = true;
                        if (angular.isDefined(item.children)) {
                            angular.forEach(item.children, function (child) {
                                if (child.state === toState.name) {
                                    item.selected = true;
                                    item.collapsed = false;
                                    child.selected = true;
                                } else {
                                    child.selected = false;
                                }
                            });
                        }
                    });
                });
            }
        };
    }

}());