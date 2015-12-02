package cz.muni.fi.pv021.TicTacToeBuilder;

import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 *
 * @author Jakub Peschel
 */
public final class TicTacToeBuilder {

    public static void main(String[] args) {
        if (args.length < 2 && args.length >= 4) {
            Logger.getLogger("main").log(Level.SEVERE, "Invalid command line " + args.length);
            System.exit(1);
        }

        TicTacToeBuilder builder;

        try {
            if (args.length == 3) {
                builder = new TicTacToeBuilder(args[0], args[1], Boolean.parseBoolean(args[2]));
            } else {
                builder = new TicTacToeBuilder(args[0], args[1], true);
            }
        } catch (IOException ex) {
            Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot read resources.", ex);
        }

    }

    private BufferedImage gamePlan;
    private BufferedImage cross;
    private BufferedImage circle;
    private final int LINE_SIZE = 1;
    private String outPath;
    private Random gen = new Random();
    private ClassLoader loader = getClass().getClassLoader();

    public TicTacToeBuilder(String path, String outPath, boolean random) throws IOException {
        cross = ImageIO.read(loader.getResource("Cross.bmp"));
        circle = ImageIO.read(loader.getResource("Circle.bmp"));
        this.outPath = outPath;
        BufferedReader br = new BufferedReader(new FileReader(path));
        String line = null;
        int i = 0;
        while ((line = br.readLine()) != null) {
            try {
                final String[] split = line.split(",");
                if (random) {
                    this.composeRandom(split[0], i, split[1]);
                } else {
                    this.composeFixed(split[0], i, split[1]);
                }
            } catch (IOException ex) {
                Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot write result" + i, ex);
            }
            i++;
        }
    }

    public void composeRandom(String gameplanSetUp, int number, String gameResult) throws IOException {
        gamePlan = ImageIO.read(loader.getResource("GamePlan20x20.bmp"));
        int squareSize = (gamePlan.getWidth() - 2) / 3;
        int randomMax = squareSize - circle.getWidth();
        String[] setUp = gameplanSetUp.split(" ");
        int i = 0;
        for (String item : setUp) {
            int posx = i % 3;
            int posy = i / 3;
            switch (item) {
                case "1":
                    gamePlan.createGraphics().drawImage(
                            (cross),
                            null,
                            ((squareSize + LINE_SIZE) * posx) + gen.nextInt(randomMax + 1),
                            ((squareSize + LINE_SIZE) * posy) + gen.nextInt(randomMax + 1)
                    );

                    break;
                case "-1":
                    gamePlan.createGraphics().drawImage(
                            circle,
                            null,
                            ((squareSize + LINE_SIZE) * posx) + gen.nextInt(randomMax + 1),
                            ((squareSize + LINE_SIZE) * posy) + gen.nextInt(randomMax + 1)
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

    public void composeFixed(String gameplanSetUp, int number, String gameResult) throws IOException {
        gamePlan = ImageIO.read(loader.getResource("GamePlan20x20.bmp"));
        int squareSize = (gamePlan.getWidth() - 2) / 3;
        int randomMax = squareSize - circle.getWidth();
        String[] setUp = gameplanSetUp.split(" ");
        int i = 0;
        for (String item : setUp) {
            int posx = i % 3;
            int posy = i / 3;
            switch (item) {
                case "1":
                    gamePlan.createGraphics().drawImage(
                            (cross),
                            null,
                            ((squareSize + LINE_SIZE) * posx) + gen.nextInt(randomMax + 1),
                            ((squareSize + LINE_SIZE) * posy) + gen.nextInt(randomMax + 1)
                    );

                    break;
                case "-1":
                    gamePlan.createGraphics().drawImage(
                            circle,
                            null,
                            ((squareSize + LINE_SIZE) * posx) + gen.nextInt(randomMax + 1),
                            ((squareSize + LINE_SIZE) * posy) + gen.nextInt(randomMax + 1)
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
