package cz.muni.fi.pv021.TicTacToeBuilder;

import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 *
 * @author Jakub Peschel
 */
public final class TicTacToeBuilder {

    public static void main(String[] args) {
        if (args.length != 4) {
            System.err.println("Invalid args number:  " + args.length);
            System.exit(1);
        }

        TicTacToeBuilder builder;

        String inputFilePath = args[0];
        String outputFilePath = args[1];
        int gamePlanSize = Integer.parseInt(args[2]);
        int limit = Integer.parseInt(args[3]);

        try {
            builder = new TicTacToeBuilder(inputFilePath, outputFilePath, gamePlanSize, limit);

        } catch (IOException ex) {
            Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot read resources.", ex);
        }

    }

    private BufferedImage gamePlan;
    private final BufferedImage cross;
    private final BufferedImage circle;
    private final int LINE_SIZE = 1;
    private final String outPath;
    private final Random gen = new Random();
    private final ClassLoader loader = getClass().getClassLoader();
    private final int limit;

    public TicTacToeBuilder(String path, String outPath, int gamePlanSize, int limit) throws IOException {
        cross = ImageIO.read(loader.getResource("Cross.bmp"));
        circle = ImageIO.read(loader.getResource("Circle.bmp"));
        this.limit = limit;
        this.outPath = outPath;
        BufferedReader br = new BufferedReader(new FileReader(path));
        iterateThrougDataset(br, gamePlanSize);
    }

    private void iterateThrougDataset(BufferedReader br, int gamePlanSize) throws IOException {
        String line;
        int i = 0;
        while ((line = br.readLine()) != null) {
            try {
                final String[] split = line.split(",");
                switch (gamePlanSize) {
                    case 0:
                        this.composeOneLine(split[0], i, GamePlan.SIZE_11);
                        break;
                    case 1:
                        this.composeOneLine(split[0], i, GamePlan.SIZE_14);
                        break;
                    case 2:
                        this.composeOneLine(split[0], i, GamePlan.SIZE_20);
                        break;
                }
            } catch (IOException ex) {
                Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.SEVERE, "Cannot write result" + i, ex);
            }
            i++;
        }
    }

    public void composeOneLine(String gameplanSetUp, int numberOfDataLine, GamePlan size) throws IOException {
        gamePlan = ImageIO.read(loader.getResource(size.toString()));
        int squareSize = (gamePlan.getWidth() - (2 * LINE_SIZE)) / 3;
        int squareSpace = squareSize - circle.getWidth();

        String[] setUp = gameplanSetUp.split(" ");
        List<GameConfig> gameConfigs = new ArrayList(generateGameConfigs(setUp, squareSpace));

        int numberOfConfig = 0;
        for (GameConfig config : gameConfigs) {
            composeOneBMP(config, numberOfDataLine, numberOfConfig, squareSize, size);
            numberOfConfig++;
        }

    }

    private Collection<GameConfig> generateGameConfigs(String[] setUp, int squareSpace) {
        Set<GameConfig> result = new HashSet();
        int perms = (int) Math.pow((Math.pow(squareSpace+1,2)), 9);
        while (result.size() < limit) {
            int configNumber = gen.nextInt(perms);
            result.add(getOneGameConfig(configNumber, (int) (Math.pow(squareSpace+1,2)), squareSpace+1, setUp));
        }
        return result;
    }

    private GameConfig getOneGameConfig(int configNumber, int squareSpace, int cellSpace, String[] setUp) {
        //generování jedné konfigurace
        int ki = configNumber;
        GameConfig conf = new GameConfig();
        for (int i = 1; i <= 9; i++) {
            int li = (int) (ki % squareSpace);
            FieldConfig field = new FieldConfig();
            field.plusx = li % cellSpace;
            field.plusy = li / cellSpace;
            field.type = setUp[i-1];
            conf.fields.add(field);
            ki = (int) (ki / squareSpace);
        }
        return conf;
    }

    private void composeOneBMP(
            GameConfig gameConfig,
            int numberOfDataLine,
            int numberOfConfig,
            int squareSize,
            GamePlan size
    ) throws IOException {
        gamePlan = ImageIO.read(loader.getResource(size.toString()));
        int i = 0;
        for (FieldConfig item : gameConfig.fields) {
            int posx = i % 3;
            int posy = i / 3;
            setSquare(item.type, posx, item.plusx, posy, item.plusy, squareSize);
            i++;

        }
        final File result = new File(this.outPath + numberOfDataLine + "_" + numberOfConfig + ".bmp");
        result.mkdirs();
        ImageIO.write(gamePlan, "bmp", result);
        Logger.getLogger(TicTacToeBuilder.class.getName()).log(Level.INFO, "Result writtern in:" + result.getAbsolutePath());
    }

    private void setSquare(String item, int posx, int xplus, int posy, int yplus, int squareSize) {
        switch (item) {
            case "1":
                gamePlan.createGraphics().drawImage(
                        (cross),
                        null,
                        ((squareSize + LINE_SIZE) * posx) + xplus,
                        ((squareSize + LINE_SIZE) * posy) + yplus
                );

                break;
            case "-1":
                gamePlan.createGraphics().drawImage(
                        circle,
                        null,
                        ((squareSize + LINE_SIZE) * posx) + xplus,
                        ((squareSize + LINE_SIZE) * posy) + yplus
                );
                break;
        }
    }

}

class GameConfig {

    final List<FieldConfig> fields = new ArrayList<>();
}

class FieldConfig {

    int plusx;
    int plusy;
    String type;
}
