var backendServiceStub = {

    getAuthorsWithPrefix:
        function () {

        },

    getDocumentsByAuthorId:
        function () {

        },

    getDocumentByTitleAndAuthor:
        function (documentTitle, authorName) {
            var document = {
                title: documentTitle,
                author: authorName,
                user: 'foo@bar.fake',
                cover: 'sample.png',
                rating: '2',
                content: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque.'
            };
            return JSON.stringify(document);
        },

    getDocumentsByBooleanExpression:
        function () {

        },


    getDocumentsByQuery:
        function () {

        },

    getDocumentsByRelevance:
        function () {

        },

    userLogin:
        function (email, password) {
            var userdata = {
                DEFAULT_AVATAR: '1',
                email: email,
                name: 'Mr.FooBar',
                password: password,
                admin: false,
                avatar: 10
            };
            return JSON.stringify(userdata);
        },

    userRegister:
        function () {

        },

    userUpdate:
        function () {

        },

    userDelete:
        function () {

        },

    getCurrentUserDocuments:
        function () {

        },

    getCurrentUserFavourites:
        function () {

        },

    storeNewDocument:
        function () {

        },

    updateDocument:
        function () {

        },

    deleteDocument:
        function () {

        },

    userLogout:
        function () {

        },

    searchForAllDocuments:
        function () {
            var documents = [
                {
                    title: 'a',
                    author: 'a',
                    user: 'foo@bar.fake',
                    cover: 'sample.png',
                    rating: '2',
                    content: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque.'
                },
                {
                    title: 'b',
                    author: 'b',
                    user: 'foo@bar.fake',
                    cover: 'sample.png',
                    rating: '2',
                    content: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque.'
                },
                {
                    title: 'c',
                    author: 'c',
                    user: 'foo@bar.fake',
                    cover: 'sample.png',
                    rating: '2',
                    content: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque.'
                },
                {
                    title: 'd',
                    author: 'd',
                    user: 'foo@bar.fake',
                    cover: 'sample.png',
                    rating: '2',
                    content: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae velit mauris. Aenean tincidunt ipsum sit amet enim vehicula, vitae tincidunt risus sollicitudin. Aliquam malesuada eget metus venenatis dictum. Vivamus luctus euismod dui, vel efficitur nisl congue ac. Vivamus ante sapien, consectetur non lacinia sollicitudin, varius a quam. Aenean ac turpis est. Donec efficitur sem vehicula viverra pellentesque. In hac habitasse platea dictumst. Aliquam felis urna, mattis sed facilisis quis, consequat at purus. Vivamus a pretium orci. Nullam sit amet congue odio. Nam laoreet enim nec arcu venenatis varius. Quisque velit mi, tempus quis suscipit in, vestibulum vitae nulla. In vitae magna leo. Phasellus at tristique neque.'
                }
            ];
            return JSON.stringify(documents);
        },

    importDocument:
        function () {

        },

    exportDocument:
        function () {

        },

    rateDocument:
        function () {

        },

    isDocumentFavourite:
        function () {
            var rand = Math.floor((Math.random() * 10) % 2);
            return !!rand;
        },

    addFavourite:
        function () {

        },

    removeFavourite:
        function () {

        },

    getMyRating:
        function () {
            return 2;
        }


};