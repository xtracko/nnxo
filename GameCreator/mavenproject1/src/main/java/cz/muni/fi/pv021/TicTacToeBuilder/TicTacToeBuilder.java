package cz.muni.fi.pv021.TicTacToeBuilder;

import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 *
 * @author Jakub Peschel
 */
public class TicTacToeBuilder {

    public static void main(String[] args) {
        if (args.length != 2) {
            Logger.getLogger("main").log(Level.SEVERE, "Invalid command line, exactly two argument required");
            System.exit(1);
        }

        TicTacToeBuilder builder;

        try {
            builder = new TicTacToeBuilder(args[0], args[1]);
        } catch (IOException ex) {
            Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot read resources.", ex);
            return;
        }

    }

    private BufferedImage gamePlan;
    private BufferedImage cross;
    private BufferedImage circle;
    private final int LINE_SIZE = 1;
    private String outPath;

    public TicTacToeBuilder(String path, String outPath) throws IOException {
        ClassLoader loader = getClass().getClassLoader();
        gamePlan = ImageIO.read(loader.getResource("GamePlan.bmp"));
        cross = ImageIO.read(loader.getResource("Cross.bmp"));
        circle = ImageIO.read(loader.getResource("Circle.bmp"));
        this.outPath = outPath;
        BufferedReader br = new BufferedReader(new FileReader(path));
        String line = null;
        int i = 0;
        while ((line = br.readLine()) != null) {
            try {
                final String[] split = line.split(",");
                this.compose(split[0], i, split[1]);
            } catch (IOException ex) {
                Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot write result" + i, ex);
            }
            i++;
        }
    }

    public void compose(String gameplanSetUp, int number, String gameResult) throws IOException {
        String[] setUp = gameplanSetUp.split(" ");
        Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.INFO, "gameplan: " + gameplanSetUp);
        int i = 0;
        for (String item : setUp) {
            Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.INFO, "znak" + i + " : "  + item);
            int posx = i % 3;
            int posy = i / 3;
            switch (item) {
                case "1":
                    gamePlan.createGraphics().drawImage(
                            (cross),
                            null,
                            (cross.getWidth() + LINE_SIZE) * posx,
                            (cross.getHeight() + LINE_SIZE) * posy
                    );
                    Logger.getLogger(TicTacToeBuilder.class.getName()).log(
                            Level.INFO, "[" + cross.getWidth() + "," + cross.getHeight() + "] "
                            + "pozice:[" + ((cross.getWidth() + LINE_SIZE) * posx) + ","
                            + ((cross.getHeight() + LINE_SIZE) * posy) + "]"
                    );

                    break;
                case "-1":
                    gamePlan.createGraphics().drawImage(
                            circle,
                            null,
                            (circle.getWidth() + LINE_SIZE) * posx,
                            (circle.getHeight() + LINE_SIZE) * posy
                    );
                    Logger.getLogger(TicTacToeBuilder.class.getName()).log(
                            Level.INFO, "[" + cross.getWidth() + "," + cross.getHeight() + "] "
                            + "pozice:[" + ((cross.getWidth() + LINE_SIZE) * posx) + ","
                            + ((cross.getHeight() + LINE_SIZE) * posy) + "]"
                    );
                    break;
            }
            i++;
        }
        final File result = new File(this.outPath + number + ".bmp");
        result.mkdirs();
        ImageIO.write(gamePlan, "bmp", result);
        Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.INFO, "Result writtern in:" + result.getAbsolutePath());
    }

}
