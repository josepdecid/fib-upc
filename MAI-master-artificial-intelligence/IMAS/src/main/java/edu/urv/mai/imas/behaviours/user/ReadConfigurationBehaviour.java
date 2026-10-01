package edu.urv.mai.imas.behaviours.user;

import edu.urv.mai.imas.helpers.Configuration;
import edu.urv.mai.imas.helpers.Constants;
import edu.urv.mai.imas.helpers.MessageUtils;
import jade.core.behaviours.OneShotBehaviour;
import jade.lang.acl.ACLMessage;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLDecoder;

public class ReadConfigurationBehaviour extends OneShotBehaviour {
    private String configurationFileName;

    public ReadConfigurationBehaviour(String configurationFileName) {
        this.configurationFileName = configurationFileName;
    }

    @Override
    public void action() {
        Configuration configuration = readData();

        ACLMessage msg = MessageUtils.createMessage(ACLMessage.INFORM, Constants.MANAGER_AID);
        try {
            msg.setContentObject(configuration);
        } catch (IOException e) {
            e.printStackTrace();
        }

        myAgent.send(msg);
    }

    /**
     * @return
     */
    private Configuration readData() {
        try {
            File f = getConfigurationFile();

            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();

            Document doc = dBuilder.parse(f);
            doc.getDocumentElement().normalize();

            return new Configuration(doc);

        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    /**
     * Read XML file containing the specific configuration simulation.
     *
     * @return Configuration file.
     * @throws UnsupportedEncodingException If file encoding is not UTF-8.
     */
    private File getConfigurationFile() throws UnsupportedEncodingException, FileNotFoundException {
        String fileName = String.format("settings/%s.xml", this.configurationFileName);
        URL url = getClass().getClassLoader().getResource(fileName);
        if (url == null) {
            throw new FileNotFoundException(String.format("File '%s' not found", this.configurationFileName));
        } else {
            String path = URLDecoder.decode(url.getFile(), "UTF-8");
            return new File(path);
        }
    }
}
