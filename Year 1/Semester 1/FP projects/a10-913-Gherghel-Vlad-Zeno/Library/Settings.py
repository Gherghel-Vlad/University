import configparser


class Settings:
    def __init__(self):
        self.config = configparser.ConfigParser()
        self.config.read("settings.properties")

    def get_repository_type(self):
        """
        Gets the repo type from the settings.properties
        :return: The string representation of the value representing which type of repo to use
        """
        return str(self.config["Settings"]["repository"])

    def get_books_file_name(self):
        """
        Gets the books file name from the settings.properties
        :return: The books file name property (string)
        """
        return str(self.config["Settings"]["books"])

    def get_clients_file_name(self):
        """
        Gets the clients file name from the settings.properties
        :return: The clients file name property (string)
        """
        return str(self.config["Settings"]["clients"])

    def get_rentals_file_name(self):
        """
        Gets the rentals file name from the settings.properties
        :return: The rentals file name property (string)
        """
        return str(self.config["Settings"]["rentals"])

    def get_ui_type(self):
        """
        Gets the ui type from the settings.properties
        :return: The ui property (string)
        """
        return str(self.config["Settings"]["ui"])

    def get_database_path(self):
        """
        Gets the path to the database
        :return: The path to the data string (string)
        """
        return str(self.config["Settings"]["database"])