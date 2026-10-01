INSERT INTO users(email, user_name, password, admin) VALUES
  ('admin@admin.admin', 'admin', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', 1),
  ('user@user.user', 'user', '04f8996da763b7a969b1028ee3007569eaf3a635486ddab211d512c85b9df8fb1', 0),
  ('valles@cs.upc.edu', 'Borja Valles', 'fff5fc9b5777031e6ee5b1c7f2d2ea9bddfae5e2c33eea4c0c9e9ab505c7cdba', 1),
  ('guillermo.valentin@est.fib.upc.edu', 'Guillermo Valentin', '803e32ba34b43ea5d857c8c6f6251fcbafc02387164e8a919d91485871864793', 1),
  ('josep.de.cid@est.fib.upc.edu', 'Josep de Cid', '2ea3314ac471788030cccbe48b8375f6e79ab5f3203d2368d42f1d5435fbadc6', 1),
  ('gabriel.puigdemunt@est.fib.upc.edu', 'Gabriel Puigdemunt', 'ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc', 1),
  ('aleix.boixader@est.fib.upc.edu', 'Aleix Boixader', '90464100c6e6370dd296bda01aa325c22078952ca99d3f9f991317ea2798a91c', 1);
-- Passwords are the names (hashed 256-SHA)

INSERT INTO authors(author_name) VALUES
  ('Alicia Ortiz'),
  ('Carl Sagan'),
  ('Chema Alonso'),
  ('Daniel Defoe'),
  ('Edgar Allan Poe'),
  ('Erasmo de Rotterdam'),
  ('James Fenimore Cooper'),
  ('Jane Austen'),
  ('Miguel de Cervantes'),
  ('Oscar Wilde'),
  ('Paul J. Steinhardt'),
  ('Stephen Hawking'),
  ('Tom Sharpe');


INSERT INTO documents(title, author_name, user_owner, term_frequency, content) VALUES
  ('A pale blue dot', 'Carl Sagan', 'valles@cs.upc.edu', '{}', 'Apalebluedot.txt'),
  ('Busqueda mediante transformación de claves', 'Alicia Ortiz', 'valles@cs.upc.edu', '{}', 'Busquedamediantetransformacióndeclaves.txt'),
  ('Corazon delator', 'Edgar Allan Poe', 'valles@cs.upc.edu', '{}', 'Corazondelator.txt'),
  ('Don Quijote de la Mancha', 'Miguel de Cervantes', 'valles@cs.upc.edu', '{}', 'DonQuijotedelaMancha.txt'),
  ('El fantasma de Canterville', 'Oscar Wilde', 'valles@cs.upc.edu', '{}', 'ElfantasmadeCanterville.txt'),
  ('El retrato de Dorian Gray', 'Oscar Wilde', 'valles@cs.upc.edu', '{}', 'ElretratodeDorianGray.txt'),
  ('El ruiseñor y la rosa', 'Oscar Wilde', 'valles@cs.upc.edu', '{}', 'Elruiseñorylarosa.txt'),
  ('El universo y su quinta esencia', 'Paul J. Steinhardt', 'valles@cs.upc.edu', '{}', 'Eluniversoysuquintaesencia.txt'),
  ('El último mohicano', 'James Fenimore Cooper', 'valles@cs.upc.edu', '{}', 'Elúltimomohicano.txt'),
  ('Elogio de la locura', 'Erasmo de Rotterdam', 'valles@cs.upc.edu', '{}', 'Elogiodelalocura.txt'),
  ('Funciones Hash', 'Chema Alonso', 'valles@cs.upc.edu', '{}', 'FuncionesHash.txt'),
  ('La historia del tiempo', 'Stephen Hawking', 'guillermo.valentin@est.fib.upc.edu', '{}', 'Lahistoriadeltiempo.txt'),
  ('Persuasión', 'Jane Austen', 'guillermo.valentin@est.fib.upc.edu', '{}', 'Persuasión.txt'),
  ('Robinson Crusoe', 'Daniel Defoe', 'guillermo.valentin@est.fib.upc.edu', '{}', 'RobinsonCrusoe.txt'),
  ('Sentido y sensibilidad', 'Jane Austen', 'Josep de Cid', '{}', 'Sentidoysensibilidad.txt'),
  ('Wilt', 'Tom Sharpe', 'Josep de Cid', '{}', 'wilt.txt');
