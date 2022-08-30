# Console-chat
Автор - Жегин Константин
Описание идеи: объект класса Message хранит данные об авторе, получателе, и текст сообщения. При входе пользователя в чат, он получает историю сообщений с последнего запуска программы, отправленных в общий чат, лично ему, или им самим.
Объект класса User содержит логин, пароль, и имя пользователя.
Класс Chat отвечает за логику программы. Метод Initialize сохраняет данные логинов пользователей из файла в оперативную память. Метод loginMenu реализует вход или регистрацию пользователя (а также выход из программы). Метод chatMenu, вызываемый после успешного входа, реализует сам чат. Методы Login и SignUp вызываются в зависимости от выбранного типа входа пользователя, проверяют корректность его данных и возвращают результат входа (0 - успешно, другие результаты - вход неудачен. В случае неудачи пользователю предлагается войти снова.